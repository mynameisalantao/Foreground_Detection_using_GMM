// import library
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <math.h>

// namespace
using namespace cv;
using namespace std;

// Function prototype
Mat read_image(void);
//void GMM_update(float weight[], float mean[], float std[], Mat);
//void GMM_update(Mat);
void matrix_product(float *, float *, float *, int, int, int);


// Picture parameter
const int num_Gaussian = 3;                        // Gaussian model的數量
const int image_row = 480;                         // 圖片長度
const int image_col = 640;                         // 圖片寬度


// Parameter matrix
float GMM_w[image_row][image_col][num_Gaussian];           // [圖片長度,圖片寬度,Gaussian]        每個高斯模型的權重
float GMM_mean[image_row][image_col][num_Gaussian][3];     // [圖片長度,圖片寬度,Gaussian,BGR]    每個高斯模型的平均值
float GMM_std[image_row][image_col][num_Gaussian];         // [圖片長度,圖片寬度,Gaussian]        每個高斯模型的標準差


// main
int main() {




	// 進行迭代運算
	
	for (int iter = 0; iter < 1; iter++) {
		Mat image = read_image();
		//GMM_update(&GMM_w[0][0][0], &GMM_mean[0][0][0][0], &GMM_var[0][0][0], image);



	}

	Mat image = read_image();
	imshow("picture", image);
	cout << "ok!";

	float k1[2][3] = { {1,2,3},{4,5,6} };
	float k2[3][3] = { {1,2,3},{4,5,6},{7,8,9} };
	float k3[2][3] = {0};
	
	matrix_product(k1[0], k2[0], k3[0], 2, 3, 3);

	
	for (int ii = 0; ii < 2; ii++) {
		for (int jj = 0; jj < 3; jj++) {
			cout << k3[ii][jj]<<" ";
		}
		cout << endl;
	}
	







	waitKey(0); // 等待一次按鍵，程式結束



	/*
	String imageName("C:\\Users\\alan\\Desktop\\HW1_dataset\\input\\in000001.png");
	Mat image;
	image = imread(imageName);//讀入圖片資料
	if (image.empty()) {
		cout << "Fuck can't read";
	}
	
	cout << "The column is " << image.cols << endl;        // 長度(行數)
	cout << "The row is " << image.rows << endl;           // 寬度(列數)
	cout << "The data type is " << image.type() << endl;   // Data type
	*/

	/*Data type*/
	/*
	            C1	C2	C3	C4
		CV_8U	0	8	16	24
		CV_8S	1	9	17	25
		CV_16U	2	10	18	26
		CV_16S	3	11	19	27
		CV_32S	4	12	20	28
		CV_32F	5	13	21	29
		CV_64F	6	14	22	30
    */

	/*
	Mat image2(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0)); // scalar將圖像設置成單一灰度和顏色(Blue, Green, Red)

	
	for (int row = 0; row < image.rows; row++) {
		for (int col = 0; col < image.cols; col++) {
			image2.at<cv::Vec3b>(row, col)[0] = image.at<cv::Vec3b>(row, col)[0];
			image2.at<cv::Vec3b>(row, col)[1] = image.at<cv::Vec3b>(row, col)[1];
			image2.at<cv::Vec3b>(row, col)[2] = image.at<cv::Vec3b>(row, col)[2];
		}
	}
	*/


	//imshow("picture", image2);                // Show our image inside it.

	/*
	const int num_Gaussian = 3;                        // Gausian model的數量


	const int image_row = 480;
	const int image_col = 640;

	cout << image_row << " " << image_col << " " << num_Gaussian << " " << endl;


	float GMM_coefficient[10][20][30][3][3];     // [圖片列數,圖片行數,高斯分布數量,BGR通道,weight+mean+variance]
	*/



	/*
	float coefficient[12][10][4];

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 4; k++) {
				coefficient[i][j][k] = i + j + k;
			}
		}
	}

	for (int i = 1; i < 2; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 4; k++) {
				cout << coefficient[i][j][k];
			}
			cout << endl;
		}
	}
	*/




	//cout << coefficient[1][2] << endl;





	
	//system("pause");
	return 0;

}

Mat read_image(void) {
	String imageName("C:\\Users\\alan\\Desktop\\HW1_dataset\\input\\in000001.png");
	Mat image;
	image = imread(imageName);//讀入圖片資料
	if (image.empty()) {
		cout << "Fuck can't read";
	}
	return image;
}




/*
//void GMM_update(float weight[],float mean[],float std[], Mat image) {
void GMM_update(Mat image) {
	int afa = 0.0001;                                        // learning rate
	// 依序處理每個pixel
	for (int row = 0; row < image_row; row++) {
		for (int col = 0; col < image_col; col++) {
			// 依序處理每個高斯分布
			int gaussian_flag = 0;                             // 記錄其所屬高斯分布
			//int gaussian;                                      // 正處理到第幾個Guassian
			// 檢查新的資料屬於哪個高斯分布
			for (int gaussian=0; gaussian < num_Gaussian; gaussian++) {
				int sum_of_mean_differ = 0;                    // 新資料與該高斯分布平均值的累計距離
				//依序計算BGR
				for (int BGR = 0; BGR < 3; BGR++) {
					int differ = pow(image.at<cv::Vec3b>(row, col)[BGR]- GMM_mean[row][col][gaussian][BGR],2);  // 平方加總
					sum_of_mean_differ += differ;
				}
				// 與該高斯分布平均值相距幾倍標準差
				int var_differ = sqrt(sum_of_mean_differ) / GMM_std[row][col][gaussian];
				// 若距離在2.5倍標準差以內，則被歸類為該高斯模型中
				if (var_differ <= 2.5) {
					gaussian_flag = gaussian;                   // 後續只會對第gaussian_flag個高斯分布做修正
					break;
				}
			// 修正gaussian_flag高斯分布的weight
			GMM_w[row][col][gaussian_flag] = (1 - afa) * GMM_w[row][col][gaussian_flag] + afa;

			// 要先算出 tho~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			float mean[] = 


			// 修正gaussian_flag高斯分布的mean
			for (int BGR = 0; BGR < 3; BGR++) {
				GMM_mean[row][col][gaussian_flag][BGR] = 
			}


			GMM_mean[image_row][image_col][num_Gaussian][3]


				//GMM_w[row][col][gaussian]
			}

		}
	}

}
*/


void matrix_product(float *matrix1, float *matrix2, float *matrix_result, int matrix1_dim0, int matrix1_dim1, int matrix2_dim1) {
// matrix_result為相乘後的結果, matrix1_dim0為矩陣1的列數, matrix1_dim1為矩陣1的行數或矩陣2的列數, matrix2_dim1為矩陣2的行數
	for (int matrix_result_row = 0; matrix_result_row < matrix1_dim0; matrix_result_row++) {
		for (int matrix_result_col = 0; matrix_result_col < matrix2_dim1; matrix_result_col++) {
			for (int element_count = 0; element_count < matrix1_dim1; element_count++) {
				*(matrix_result + matrix_result_row * matrix1_dim1 + matrix_result_col) += *(matrix1 + matrix_result_row * matrix1_dim1 + element_count)**(matrix2 + element_count * matrix2_dim1 + matrix_result_col);
			}
		}
	}	
}
