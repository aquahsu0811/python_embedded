#include <iostream>
#include <Python.h>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;

PyObject * pModule = NULL;

void Hello()
{   
    PyObject * pFunc = NULL;   
    pFunc = PyObject_GetAttrString(pModule, "Hello"); //Call python function
    PyEval_CallObject(pFunc, NULL);
}

void Add()
{
    PyObject * pFunc = NULL;
    pFunc = PyObject_GetAttrString(pModule, "Add");
    PyObject *pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 6));
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 8));
    //return value
    PyObject *pReturn = NULL;
    pReturn = PyEval_CallObject(pFunc, pArgs);
    int result;
    PyArg_Parse(pReturn, "i", &result);
    cout << "6 + 8 = " << result << endl;
}

void passStr(std::string s) 
{
    PyObject *pFunc;
    PyObject *pArgs, *pValue;

    /* great_module.great_function */
    pFunc = PyObject_GetAttrString(pModule, "getStr");
    /* build args */
    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs,0, PyUnicode_FromString(s.c_str()));
    pValue = PyObject_CallObject(pFunc, pArgs);
}

void dImg(cv::Mat img)
{
    PyObject * pFunc = NULL;
    PyObject *pArgs, *pArg, *pResult;
    pFunc = PyObject_GetAttrString(pModule, "detect");
    pArgs = PyTuple_New(4);

    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    pArg = PyByteArray_FromStringAndSize((char*)img.data, img.total() * img.elemSize());
   
    PyTuple_SetItem(pArgs, 0, pArg);
    PyTuple_SetItem(pArgs, 1, PyLong_FromLong(img.cols));
    PyTuple_SetItem(pArgs, 2, PyLong_FromLong(img.rows));
    PyTuple_SetItem(pArgs, 3, PyLong_FromLong(img.channels()));

    pResult = PyObject_CallObject(pFunc, pArgs);
    
    Py_DECREF(pArgs);

    if (PyList_Check(pResult)) {
        int SIZE = PyList_Size(pResult);
        float *arr = new float(SIZE);
        for (int i = 0; i < SIZE; i++) arr[i] = PyFloat_AsDouble(PyList_GetItem(pResult, i));
        for (int i = 0; i < SIZE ; i++) 
        {
            printf("%f, ", arr[i]);
            printf("\n");
        }
    }
}

int main()
{
    Py_Initialize(); // Initial python path
    PyRun_SimpleString("import sys");  
	PyRun_SimpleString("sys.path.append('./')"); // Setup python_module path
    pModule = PyImport_ImportModule("python_module");//呼叫的Python檔名

    if (pModule == NULL) {
        printf("ERROR importing python module");
        return 0;
    } 

    Hello();

    Add();

    passStr("test");

    cv::Mat img = cv::imread("./cat.jpg");
    dImg(img);
    
    Py_Finalize();

    return 0;
}