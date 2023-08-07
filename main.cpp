#include <opencv2/opencv.hpp>
#include <Logger.h>
#include <Windows.h>
#include <string>
SNSTART("splitVedio")
bool OpenFileSelectionDialog(std::string& selectedFilePath) {
    OPENFILENAME ofn;
    char szFile[260] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Video Files\0*.mp4;*.avi;*.mkv;*.m2t;\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE) {
        selectedFilePath = ofn.lpstrFile;
        return true;
    } else {
        return false;
    }
}

int main() {
    system("chcp 65001");
    auto path=std::string("");
    OpenFileSelectionDialog(path);
    linfo("get file: "+path);
    linfo("start");
    if (path.size()<=0)
    {
        linfo("close for no input file");
        return -1;
    }
        //cv::VideoCapture cap("E:\\BaiduNetdiskDownload\\数学\\NHK Kouhaku Uta Gassen - 57th NHK Kouhaku Uta Gassen (2006-12-31) (HDTV - MPEG2)\\NHK Kouhaku Uta Gassen - 57th NHK Kouhaku Uta Gassen (2006-12-31) (HDTV - MPEG2).m2t");  // Replace with your video file path
    cv::VideoCapture cap(path);
    if (!cap.isOpened()) {
        lerror("Error opening video file." );
        return -1;
    }

    // Set the start time (in milliseconds)
    int start_time_ms = 5000;  // 5 seconds
    int end_time_ms = 15000;   // 15 seconds

    cap.set(cv::CAP_PROP_POS_MSEC, start_time_ms);

    while (true) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty() || cap.get(cv::CAP_PROP_POS_MSEC) > end_time_ms)
            break;

        // Do processing on the frame here, if needed
        cv::imshow("Captured Video", frame);

        char key = cv::waitKey(1);
        if (key == 'q')
            break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
