import sys
import subprocess

if "matplotlib" not in sys.modules:
    subprocess.call(['sh', 'tests_files/test_performances/install_matplotlib.sh'])

import matplotlib.pyplot as plt

with open("tests_files/test_performances/performances.txt", "r") as file:
    var = file.readlines()

    list_plt_real = list()
    list_plt_user = list()
    list_plt_sys = list()
    list_plt_thread = list()

    for i in range(0, len(var)):
        if var[i][0:3] == 'rea':
            list_plt_real.append(float(var[i][4:-1]))
        elif var[i][0:3] == 'use':
            list_plt_user.append(float(var[i][4:-1]))
        elif var[i][0:3] == 'sys':
            list_plt_sys.append(float(var[i][3:-1]))
        else:
            list_plt_thread.append(int(var[i][:-1]))

    plt.plot(list_plt_thread, list_plt_real, color='red', label='real')
    plt.plot(list_plt_thread, list_plt_user, color='green', label='user', linewidth=0.5)
    plt.plot(list_plt_thread, list_plt_sys, color='blue', label='sys', linewidth=0.5)

    plt.xticks(list_plt_thread)

    plt.title("Different time statistics for different number of threads")
    plt.xlabel("Number of threads")
    plt.ylabel("Time (s)")
    plt.legend()

    plt.savefig("tests_files/test_performances/figPerformances.png")
