#include <Windows.h>
#include <Logger.h>
#include <string>
#include <MyFile.h>
#include <encoding.h>
#include <opencv2/opencv.hpp>
#define IDC_CHAR_INPUT 1001
#define IDC_NUM_INPUT1 1002
#define IDC_NUM_INPUT2 1003
#define IDC_BUTTON     1004
#define IDC_BUTTON_PREVIEW 1005
#define IDC_BUTTON_CUT 1006
SNSTART("form");
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 10, 150, 25, hwnd, (HMENU)IDC_CHAR_INPUT, NULL, NULL);
            CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 40, 70, 25, hwnd, (HMENU)IDC_NUM_INPUT1, NULL, NULL);
            CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 90, 40, 70, 25, hwnd, (HMENU)IDC_NUM_INPUT2, NULL, NULL);
            CreateWindow("BUTTON", "...", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 170, 10, 70, 25, hwnd, (HMENU)IDC_BUTTON, NULL, NULL);
            CreateWindow("BUTTON", "Preview", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 80, 70, 25, hwnd, (HMENU)IDC_BUTTON_PREVIEW, NULL, NULL);
            CreateWindow("BUTTON", "Cut", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 90, 80, 70, 25, hwnd, (HMENU)IDC_BUTTON_CUT, NULL, NULL);


            SetWindowText(GetDlgItem(hwnd, IDC_NUM_INPUT1), "0");
            SetWindowText(GetDlgItem(hwnd, IDC_NUM_INPUT2), "1000");

            break;
        }

        case WM_COMMAND: {
            if (LOWORD(wParam) == IDC_BUTTON) {
                char charInput[256];
                int numInput1, numInput2;

                GetWindowText(GetDlgItem(hwnd, IDC_CHAR_INPUT), charInput, sizeof(charInput));
                GetWindowText(GetDlgItem(hwnd, IDC_NUM_INPUT1), charInput, sizeof(charInput));
                numInput1 = atoi(charInput);
                GetWindowText(GetDlgItem(hwnd, IDC_NUM_INPUT2), charInput, sizeof(charInput));
                numInput2 = atoi(charInput);

                // Handle your logic here
            }
            if (HIWORD(wParam) == BN_CLICKED)
            {
                linfo("clicked " +std::to_string(reinterpret_cast<int>(HWND(wParam))));
                auto whichButton=reinterpret_cast<int>(HWND(wParam));
                if ( whichButton== IDC_BUTTON)
                {
                    auto path=std::string("");
                    OpenFileSelectionDialog(path);
                    linfo(Encoding::GbkToUtf8(path.c_str()));
                    SetWindowText(GetDlgItem(hwnd, IDC_CHAR_INPUT), path.c_str());

                } else if (whichButton==IDC_BUTTON_PREVIEW)
                {
                    char charInput[256];
                    GetWindowText(GetDlgItem(hwnd, IDC_NUM_INPUT1), charInput, sizeof(charInput));
                    int start_time_ms = std::stoi(charInput);  // 5 seconds
                    linfo("start time:" +std::string(charInput));
                    GetWindowText(GetDlgItem(hwnd, IDC_NUM_INPUT2), charInput, sizeof(charInput));
                    int end_time_ms = std::stoi(charInput);   // 15 seconds
                    linfo("end time:" +std::string(charInput));
                    ldebug(charInput);
                    GetWindowText(GetDlgItem(hwnd, IDC_CHAR_INPUT), charInput, sizeof(charInput));
                    {  cv::VideoCapture cap(Encoding::GbkToUtf8(charInput));
                        if (!cap.isOpened()) {
                            lerror("Error opening video file." );
                            auto warnMessage=std::string ("failed to open file");
                            warnMessage+=charInput;
                            MessageBox(NULL,warnMessage.c_str() , "ERROR", MB_OK | MB_ICONINFORMATION);
                            return -1;
                        }
                        // Set the start time (in milliseconds)
                        cap.set(cv::CAP_PROP_POS_MSEC, start_time_ms);
                        double frameRate = cap.get(cv::CAP_PROP_FPS);
                        double frameWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
                        double frameHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
                        linfo("framerate: "+std::to_string(frameRate));

                                             frameRate=1.0/frameRate*1000;linfo("wait time: "+std::to_string(frameRate));
                        while (true) {
                            Sleep(frameRate);//wait to adjust the frame rate.
                            cv::Mat frame;
                            cap >> frame;
                            if (frame.empty() || cap.get(cv::CAP_PROP_POS_MSEC) > end_time_ms)
                                break;
                            // Do processing on the frame here, if needed
                            cv::imshow("Captured Video", frame);
                            char key = cv::waitKey(1);
                            if (key == 'q')
                                break;
                            else if (key=='c')
                            {
                                frameRate=frameRate>10?frameRate-10:0;
                                linfo("faster " +std::to_string(frameRate));
                            }
                            else if (key=='x')
                            {
                                frameRate+=10;
                                linfo("slower " +std::to_string(frameRate));
                            }
                        }
                        cap.release();
                        cv::destroyAllWindows();}
                } else if (whichButton==IDC_BUTTON_CUT)
                {
                    char charInput[256];
                    GetWindowText(GetDlgItem(hwnd, IDC_NUM_INPUT1), charInput, sizeof(charInput));
                    int start_time_ms = std::stoi(charInput);  // 5 seconds
                    linfo("start time:" +std::string(charInput));
                    GetWindowText(GetDlgItem(hwnd, IDC_NUM_INPUT2), charInput, sizeof(charInput));
                    int end_time_ms = std::stoi(charInput);   // 15 seconds
                    linfo("end time:" +std::string(charInput));
                    ldebug(charInput);
                    GetWindowText(GetDlgItem(hwnd, IDC_CHAR_INPUT), charInput, sizeof(charInput));
                    {  cv::VideoCapture cap(Encoding::GbkToUtf8(charInput));
                        if (!cap.isOpened()) {
                            lerror("Error opening video file." );
                            auto warnMessage=std::string ("failed to open file");
                            warnMessage+=charInput;
                            MessageBox(NULL,warnMessage.c_str() , "ERROR", MB_OK | MB_ICONINFORMATION);
                            return -1;
                        }
                        // Set the start time (in milliseconds)
                        cap.set(cv::CAP_PROP_POS_MSEC, start_time_ms);
                        double frameRate = cap.get(cv::CAP_PROP_FPS);
                        double frameWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
                        double frameHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
                        linfo(std::to_string(cap.get(cv::CAP_PROP_BITRATE)));
                        linfo("framerate: "+std::to_string(frameRate));
                        linfo("frame Heighth: "+std::to_string(frameHeight));
                        linfo("frame width: "+std::to_string(frameWidth));
                        cv::VideoWriter videoWriter("output.mp4",cv::VideoWriter::fourcc('H', '2', '6', '4'), frameRate, cv::Size(frameWidth, frameHeight),{cv::VIDEOWRITER_PROP_BITRATE,4584});
                        if (!videoWriter.isOpened()) {
                            lerror("Error opening video writer.");
                            return -1;
                        }
                        videoWriter.set(cv::VIDEOWRITER_PROP_BITRATE , 4683);
                        while (true) {
                            cv::Mat frame;
                            cap >> frame;
                            if (frame.empty() || cap.get(cv::CAP_PROP_POS_MSEC) > end_time_ms)
                                break;
                            // Do processing on the frame here, if needed
                            cv::imshow("Captured Video", frame);
                            videoWriter.write(frame);
                            char key = cv::waitKey(1);
                            if (key == 'q')
                                break;
                        }
                        linfo("cut end");
                        cap.release();
                        videoWriter.release();
                        cv::destroyAllWindows();}
                }
            }
            break;
        }

        case WM_CLOSE:
            linfo("close window");
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")
int main(){
  //  system("chcp 65001");
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindow("MyWindowClass", "cut video", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 150, NULL, NULL, GetModuleHandle(NULL), NULL);
    ShowWindow(hwnd, SW_SHOWDEFAULT);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
