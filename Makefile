python_embedded: python_embedded.cpp
	g++ -std=c++11 -o python_embedded python_embedded.cpp \
    -I/home/ubuntu/Documents/cpybind \
	-I/usr/include/python3.6m \
	-I/opt/intel/openvino/opencv/include \
	-L/opt/intel/openvino/opencv/lib \
	-lpthread -lm -ldl -lpython3.6m \
	-lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gapi -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_video -lopencv_videoio
	
clean:
	rm -f python_embedded
