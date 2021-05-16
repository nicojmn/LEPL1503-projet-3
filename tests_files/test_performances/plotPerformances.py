"""
This file checks and installs if necessary matplotlib and then compute a graph of the execution time according
to the number of threads.
It uses performances.txt to collect data for making a graph
"""
import os
import sys
import subprocess
import pkg_resources

# Check of matplotlib in installed on the device
required = {'matplotlib'}
installed = {pkg.key for pkg in pkg_resources.working_set}
missing = required - installed

if missing:
    try:
        python = sys.executable
        subprocess.check_call([python, '-m', 'pip3', 'install', *missing], stdout=subprocess.DEVNULL)
    # missing the permission
    except:
        os.system('pip3 install matplotlib --user')

import matplotlib.pyplot as plt

# Plot the time performances of the different run using different number of thread
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
