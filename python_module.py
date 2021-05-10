import sys
import cv2
import numpy as np

def Hello():
    print("Hello Python")
 
def Add(a, b):
    return a+b

def GetArray():
    a = np.array([[1.1,1.2],[2.1,2.2],[3.1,3.2],[4.1,4.2]]).reshape(8,1)
    return list(a)

def detect(pI,col,row,channels):
    mat = np.asarray(pI, dtype=np.uint8)    
    I_reshape = np.asarray(list(pI), dtype=np.ubyte)
    #I_reshape = np.frombuffer(pI, dtype=np.ubyte)
    #I_reshape = np.reshape(I_reshape,(row,col,channels))
    print(I_reshape)
    #a = np.array([[1.1,1.2],[2.1,2.2],[3.1,3.2],[4.1,4.2]]).reshape(8,1)
    d = []
    d.append(10)
    d.append(16)
    d.append(50)
 
    return list(d)

def getStr(s):
    print("getStr:",s)