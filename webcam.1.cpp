#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main() {
    // Открываем веб-камеру
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Ошибка открытия камеры!" << std::endl;
        return -1;
    }

    Mat frame, gray, thresh;

    while (true) {
        cap >> frame; // Считываем кадр с камеры
        if (frame.empty()) break;

        // Преобразуем в оттенки серого
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        // Применяем бинаризацию
        threshold(gray, thresh, 100, 255, THRESH_BINARY_INV);

        // Находим контуры
        std::vector<std::vector<Point>> contours;
        findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for (const auto& contour : contours) {
            // Вычисляем ограничивающий прямоугольник для каждого контура
            Rect boundingBox = boundingRect(contour);
            if (boundingBox.width > 10 && boundingBox.height > 10) { // Фильтруем по размеру
                rectangle(frame, boundingBox, Scalar(0, 255, 0), 2); // Рисуем прямоугольник
            }
        }

        // Отображаем результат
        imshow("Frame", frame);

        // Выход по ESC
        if (waitKey(30) == 27) break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
