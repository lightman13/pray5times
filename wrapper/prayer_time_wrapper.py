# In the name of Allah

import datetime
import getopt
import sys
import subprocess
from geopy.geocoders import Nominatim

usage = "prayer_time_wrapper -h -l --location= -t --timezone= -d --duration="
prayer = "\t\tFajr\tDuhr\tAsr\tMaghrib\tIsha\n"

def process_file(date, file_h, output):
    file_h.write(str(date))

    for lines in output:
        arr = lines.split()
        file_h.write("\t" + arr[1])

    file_h.write("\n")

def launch_cmd(location, timezone, date):
    command = "prayer_time -l" + str(location.latitude) + " -L" + \
            str(location.longitude) + " -d" + str(date) + " -t" + \
            str(timezone)

    output = subprocess.check_output(command,
            shell=True, text=True,
            universal_newlines=True).splitlines()

    return output

def check_cmd():
    cmd = "ls /usr/local/bin/prayer_time"

    try:
        output = subprocess.check_output(cmd, shell=True)
        return 0
    except subprocess.CalledProcessError as output_err:
        print("You must install prayer_time. Return code",
                output_err.returncode)
        return output_err.returncode

def main():
    duration = 1
    file_h = open("prayer_times.txt", 'w')
    location = ""

    rc = check_cmd()
    if rc == 2:
        sys.exit(1)

    try:
        opt, args= getopt.getopt(sys.argv[1:], "dhl:t:", ["help", "location=",
            "timezone=", "duration="])
    except getopt.GetoptError as err:
        print(err)
        sys.exit(1)

    for option, argument in opt:
        if option in ("-h", "--help"):
            print(usage)
            sys.exit(0)
        elif option in ("-l", "--location"):
            location = argument
        elif option in ("-d", "--duration"):
            duration = int(argument)
        elif option in ("-t", "--timezone"):
            timezone = int(argument)
            if timezone < 0:
                print("Timezone must be positive integer")
                sys.exit(1)
        else:
            assert False, "unhandled option"

    if location == "":
        print("Location is mandatory option")
        print(usage)
        sys.exit(1)

    geolocator = Nominatim(user_agent="prayer_time")
    location = geolocator.geocode(location)

    file_h.write(prayer)
    today = datetime.date.today()

    for i in range(duration):
        output = launch_cmd(location, timezone, today)
        process_file(today, file_h, output)
        today += datetime.timedelta(days=1)

    file_h.close()

main()