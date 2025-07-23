#!/usr/bin/env python3

import scipy.io.wavfile as wav
import numpy as np

T = 60
fs = 16000
t=np.linspace(0,T,fs*T)

envelope = np.sin(2*np.pi*0.5/T*t)
envelope = np.where(envelope * 2 <1, envelope*2, 1) #scale and saturate to 1
x=np.sin(2*np.pi*48*t) * envelope

wav.write("test.wav", fs, x)

