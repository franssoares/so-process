#include "../include/operations.h" //uso para processamento das imagens
#include <vector> //contêiner do STL
#include <opencv2/opencv.hpp> //uso em imagens

// Função para calcular Rx
void calcularRx(const cv::Mat& I, cv::Mat& Rx) {
    int M = I.rows;
    int N = I.cols;
    int sum;

    for (int i = 1; i < M - 1; ++i) {
        for (int j = 1; j < N - 1; ++j) {
            sum = (I.at<uchar>(i+1, j-1) + I.at<uchar>(i+1, j) + I.at<uchar>(i+1, j+1)) -
                (I.at<uchar>(i-1, j-1) + I.at<uchar>(i-1, j) + I.at<uchar>(i-1, j+1));
            
            // Calcula o valor absoluto do gradiente
            sum = std::abs(sum);

            // Garante que o valor esteja no intervalo [0, 255]
            sum = std::min(sum, 255);

            Rx.at<uchar>(i, j) = static_cast<uchar>(sum);
        }
    }
}

// Função para calcular Ry
void calcularRy(const cv::Mat& I, cv::Mat& Ry) {
    int M = I.rows;
    int N = I.cols;
    int sum;

    for (int i = 1; i < M - 1; ++i) {
        for (int j = 1; j < N - 1; ++j) {
            sum = (I.at<uchar>(i-1, j+1) + I.at<uchar>(i, j+1) + I.at<uchar>(i+1, j+1)) -
                (I.at<uchar>(i-1, j-1) + I.at<uchar>(i, j-1) + I.at<uchar>(i+1, j-1));
            
            // Calcula o valor absoluto do gradiente
            sum = std::abs(sum);

            // Garante que o valor esteja no intervalo [0, 255]
            sum = std::min(sum, 255);

            Ry.at<uchar>(i, j) = static_cast<uchar>(sum);
        }
    }
}

// Função para combinar Rx e Ry
void combinarRxRy(const cv::Mat& Rx, const cv::Mat& Ry, cv::Mat& R) {
    int M = R.rows;
    int N = R.cols;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int soma = static_cast<int>(Rx.at<uchar>(i, j)) + static_cast<int>(Ry.at<uchar>(i, j));
            R.at<uchar>(i, j) = static_cast<uchar>(std::min(soma, 255));
        }
    }
}