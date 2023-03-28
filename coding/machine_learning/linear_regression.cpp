#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

int feature = 784;

struct W_B
{
    vector<double> weights;
    double bias;
};

struct ImageData
{
    vector<double> pixels;
    int label;
};

uint32_t swap_uint32(uint32_t x)
{
    x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
    return (x << 16) | (x >> 16);
}

void read_mnist_image(string filename, vector<vector<double>> &train_images)
{
    ifstream file(filename, ios::binary);                   // 以二进制形式打开filename
    int magic_number, num_images, num_rows, num_cols;       // magic_number是指文件头中的一个4字节的无符号整数，用于确定数据集的格式，数据集为2051，标签集为2049
    file.read((char *)&magic_number, sizeof(magic_number)); // 读取文件头，4个字节
    magic_number = swap_uint32(magic_number);               //__builtin_bswap32转换32位整数的字节顺序
    file.read((char *)&num_images, sizeof(num_images));
    num_images = swap_uint32(num_images); // 共6w张图片
    file.read((char *)&num_rows, sizeof(num_rows));
    num_rows = swap_uint32(num_rows);
    file.read((char *)&num_cols, sizeof(num_cols));
    num_cols = swap_uint32(num_cols);
    // 上面这段代码与数据集本身的形式有关

    for (int i = 0; i < num_images; ++i)
    { // 读取所有图像
        vector<double> train_image;
        for (int j = 0; j < num_rows * num_cols; ++j)
        { // 遍历每张图片的每一个像素值
            unsigned char pixel;
            file.read((char *)&pixel, sizeof(pixel)); // 将file中的二进制数据读取到pixel中，并将其地址强制转换为char*类型的指针，保证读取到的数据以字节为单位填充到pixel中，读取的数量为vector<double> pixel
            train_image.push_back(pixel / 255.0);     // 将像素值归一化到0到1之间
        }
        train_images.push_back(train_image);
    }
}

void read_mnist_labels(string filename, vector<int> &labels)
{
    ifstream file(filename, ios::binary);
    int magic_number = 0, num_labels = 0;
    file.read((char *)&magic_number, sizeof(magic_number));
    magic_number = __builtin_bswap32(magic_number);
    file.read((char *)&num_labels, sizeof(num_labels));
    num_labels = __builtin_bswap32(num_labels);

    for (int i = 0; i < num_labels; i++)
    {
        unsigned char label;
        file.read((char *)&label, sizeof(label));
        labels.push_back(label);
    }
}

vector<ImageData> read_mnist_data(string image_filename, string label_filename)
{
    vector<vector<double>> train_images;
    vector<int> train_labels;
    read_mnist_image(image_filename, train_images);
    read_mnist_labels(label_filename, train_labels);
    vector<ImageData> mnist_data;
    for (int i = 0; i < train_images.size(); ++i)
    {
        ImageData img;
        img.pixels = train_images[i];
        img.label = train_labels[i];
        mnist_data.push_back(img);
    }
    return mnist_data;
}

void weights_and_bias_initial(int feature, W_B & w_b){
    for (int i = 0; i < feature; i++) {
        w_b.weights.push_back(((double) rand() / RAND_MAX) - 0.5);
    }
    w_b.bias = ((double) rand() / RAND_MAX) - 0.5;
}

double predict(vector<double> input, W_B &w_b){
    double result = 0.0;
    for (int i = 0; i < feature; ++i){
        result += input[i] * w_b.weights[i]; // 每一个图的每个像素点 * 权重 再相加
    }
    result += w_b.bias; // 再加上偏差
    return result;
}

void compute_gradient(vector<ImageData> &images, int feature, W_B &w_b, W_B &grad_w_b){
    for (int i = 0; i < images.size(); i++){
        ImageData &image = images[i];
        double predicted = predict(image.pixels, w_b);
        double error = predicted - image.label; //真实值与预测值之差
        vector<double> temp_grad_weight;
        for (int j = 0; j < image.pixels.size(); j++){
            temp_grad_weight.push_back(error * image.pixels[j]);
        }
        for(int k = 0; k <image.pixels.size(); k++){
            grad_w_b.weights[k] += temp_grad_weight[k];
        }
        grad_w_b.bias += error; 
    }

    for (int i = 0; i < grad_w_b.weights.size(); ++i){
            grad_w_b.weights[i] = grad_w_b.weights[i] / images.size();
    }
    grad_w_b.bias = grad_w_b.bias / images.size();
}

// 更新模型参数
void update_parameters(W_B &w_b, W_B &grad_w_b, double learning_rate){
    for (int i = 0; i < feature; ++i){
        w_b.weights[i] -= learning_rate * grad_w_b.weights[i]; // w=w-learning-rate*grad
    }
    w_b.bias -= learning_rate * grad_w_b.bias;
}

// 计算损失函数，预测结果与真实值之间的差异
double calculate_loss(vector<ImageData> images, W_B &w_b)
{
    double loss = 0.0;
    for (int i = 0; i < images.size(); ++i)
    {
        double y = images[i].label;                    // 实际标签值
        double y_hat = predict(images[i].pixels, w_b); // 计算增加权重和偏差之后的标签值
        loss += pow(y - y_hat, 2);                     // 基于最小二乘法
    }
    return loss / images.size();
}

void train_linear_regression(vector<ImageData> &images, int num_iterations, int feature, double learning_rate, W_B &w_b, W_B &grad_w_b){
    for (int i = 0; i < num_iterations; i++){
        // vector<double> grad_weights(feature, 0.0);
        // double grad_bias = 0.0;
        compute_gradient(images, feature, w_b, grad_w_b);
        update_parameters(w_b, grad_w_b, learning_rate);
        double loss = calculate_loss(images, w_b);
        cout << "Iteration " << i + 1 << ", Loss = " << loss << endl;
    }
}

int main(){
    vector<ImageData> trainset = read_mnist_data("dataset/train-images-idx3-ubyte", "dataset/train-labels-idx1-ubyte");
//    cout << "完成数据集加载" << endl;
    W_B w_b;
    weights_and_bias_initial(feature, w_b); //调用weights_and_bias_initial，对w_b进行初始化
//    cout << "完成参数初始化" << endl;
    W_B grad_w_b;
    weights_and_bias_initial(feature, grad_w_b); //初始化一个结构体grad_w_b，并将全部的值修改为0
    for (int i=0; i < grad_w_b.weights.size(); i++){
        grad_w_b.weights[i] = 0.0;
    }
    grad_w_b.bias = 0.0;
//    cout << "完成梯度初始化" << endl;
    train_linear_regression(trainset, 200, feature, 0.01, w_b, grad_w_b);
//    cout << "完成迭代" << endl;
    return 0;
}
