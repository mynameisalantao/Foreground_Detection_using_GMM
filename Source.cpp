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
const int num_Gaussian = 3;                        // Gaussian model���ƶq
const int image_row = 480;                         // �Ϥ�����
const int image_col = 640;                         // �Ϥ��e��


// Parameter matrix
float GMM_w[image_row][image_col][num_Gaussian];           // [�Ϥ�����,�Ϥ��e��,Gaussian]        �C�Ӱ����ҫ����v��
float GMM_mean[image_row][image_col][num_Gaussian][3];     // [�Ϥ�����,�Ϥ��e��,Gaussian,BGR]    �C�Ӱ����ҫ���������
float GMM_std[image_row][image_col][num_Gaussian];         // [�Ϥ�����,�Ϥ��e��,Gaussian]        �C�Ӱ����ҫ����зǮt


// main
int main() {




	// �i�歡�N�B��
	
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
	







	waitKey(0); // ���ݤ@������A�{������



	/*
	String imageName("C:\\Users\\alan\\Desktop\\HW1_dataset\\input\\in000001.png");
	Mat image;
	image = imread(imageName);//Ū�J�Ϥ����
	if (image.empty()) {
		cout << "Fuck can't read";
	}
	
	cout << "The column is " << image.cols << endl;        // ����(���)
	cout << "The row is " << image.rows << endl;           // �e��(�C��)
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
	Mat image2(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0)); // scalar�N�Ϲ��]�m����@�ǫשM�C��(Blue, Green, Red)

	
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
	const int num_Gaussian = 3;                        // Gausian model���ƶq


	const int image_row = 480;
	const int image_col = 640;

	cout << image_row << " " << image_col << " " << num_Gaussian << " " << endl;


	float GMM_coefficient[10][20][30][3][3];     // [�Ϥ��C��,�Ϥ����,���������ƶq,BGR�q�D,weight+mean+variance]
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
	image = imread(imageName);//Ū�J�Ϥ����
	if (image.empty()) {
		cout << "Fuck can't read";
	}
	return image;
}




/*
//void GMM_update(float weight[],float mean[],float std[], Mat image) {
void GMM_update(Mat image) {
	int afa = 0.0001;                                        // learning rate
	// �̧ǳB�z�C��pixel
	for (int row = 0; row < image_row; row++) {
		for (int col = 0; col < image_col; col++) {
			// �̧ǳB�z�C�Ӱ�������
			int gaussian_flag = 0;                             // �O������ݰ�������
			//int gaussian;                                      // ���B�z��ĴX��Guassian
			// �ˬd�s������ݩ���Ӱ�������
			for (int gaussian=0; gaussian < num_Gaussian; gaussian++) {
				int sum_of_mean_differ = 0;                    // �s��ƻP�Ӱ������������Ȫ��֭p�Z��
				//�̧ǭp��BGR
				for (int BGR = 0; BGR < 3; BGR++) {
					int differ = pow(image.at<cv::Vec3b>(row, col)[BGR]- GMM_mean[row][col][gaussian][BGR],2);  // ����[�`
					sum_of_mean_differ += differ;
				}
				// �P�Ӱ������������Ȭ۶Z�X���зǮt
				int var_differ = sqrt(sum_of_mean_differ) / GMM_std[row][col][gaussian];
				// �Y�Z���b2.5���зǮt�H���A�h�Q�k�����Ӱ����ҫ���
				if (var_differ <= 2.5) {
					gaussian_flag = gaussian;                   // ����u�|���gaussian_flag�Ӱ����������ץ�
					break;
				}
			// �ץ�gaussian_flag����������weight
			GMM_w[row][col][gaussian_flag] = (1 - afa) * GMM_w[row][col][gaussian_flag] + afa;

			// �n����X tho~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			float mean[] = 


			// �ץ�gaussian_flag����������mean
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
// matrix_result���ۭ��᪺���G, matrix1_dim0���x�}1���C��, matrix1_dim1���x�}1����Ʃίx�}2���C��, matrix2_dim1���x�}2�����
	for (int matrix_result_row = 0; matrix_result_row < matrix1_dim0; matrix_result_row++) {
		for (int matrix_result_col = 0; matrix_result_col < matrix2_dim1; matrix_result_col++) {
			for (int element_count = 0; element_count < matrix1_dim1; element_count++) {
				*(matrix_result + matrix_result_row * matrix1_dim1 + matrix_result_col) += *(matrix1 + matrix_result_row * matrix1_dim1 + element_count)**(matrix2 + element_count * matrix2_dim1 + matrix_result_col);
			}
		}
	}	
}
