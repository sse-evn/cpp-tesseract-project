#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread> // Для функции sleep
#include <chrono> // Для использования chrono
using namespace std;
using namespace cv;

int main() {
    // Загружаем каскад для распознавания номеров
    CascadeClassifier plateCascade;
    if (!plateCascade.load("haarcascade_russian_plate_number.xml")) {
        std::cerr << "Ошибка загрузки каскада для распознавания номеров!" << std::endl;
        return -1;
    }

    VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Ошибка открытия камеры!" << std::endl;
        return -1;
    }

    Mat frame;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // Обнаруживаем номера
        std::vector<Rect> plates;
        plateCascade.detectMultiScale(gray, plates, 1.1, 3, 0, Size(30, 30));

        // Рисуем прямоугольники вокруг обнаруженных номеров
        for (const auto& plate : plates) {
            rectangle(frame, plate, Scalar(255, 64, 0), 2); // Красный прямоугольник

            // Здесь можно извлечь номер (например, из изображения) 
            // Для простоты мы будем использовать фиксированный текст
            string detectedNumber = "016ANG"; // Это пример, замените на реальный номер

            cout << "Обнаружен номер: " << detectedNumber << endl;

            // Задержка 4 секунда
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        imshow("Frame", frame);

        if (waitKey(30) == 'q') break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
