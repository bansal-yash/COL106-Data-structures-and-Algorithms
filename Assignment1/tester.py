import subprocess
import random

# Generate mode was used to create test cases - you only need to work with Test Mode

MODE = "TEST" # "GENERATE" or "TEST"
if(MODE == "GENERATE"):
    print("Generating test cases...")
    print("")
    test = []
else:
    print("Running tests...")
    print("")

# first check if main.cpp exists in this directory
def check_submitted_files(required_files):
    missing_files = []
    for path in required_files:
        try:
            with open(path, 'r') as f:
                pass
        except FileNotFoundError:
            missing_files.append(path)
    return missing_files

def generate_test_cases():
    test_cases = []
    for i in range(10):
        test_str = ""
        test_str += '1 0 1 1 1 2 1 2 3 1 3 4 1 4 5 1 5 6 1 6 7 1 7 8 1 8 9 1 9 10 1 10 11 '
        for j in range(100):
            # generate random number [1,9]
            command = random.randint(1, 9)
            # generate random number [0,10]
            set_num = random.randint(0, 10)
            if(command == 6 or command == 9):
                test_str += str(command) + " " + str(set_num) + " "
            elif(command == 1 or command == 2 or command == 3):
                element = random.randint(0, 10000000)
                test_str += str(command) + " " + str(set_num) + " " + str(element) + " "
            else:
                # generate random number [0,10]
                set_num2 = random.randint(0, 10)
                test_str += str(command) + " " + str(set_num) + " " + str(set_num2) + " "
        test_cases.append((test_str, "", 1))
    return test_cases

class Tester:
    def __init__(self):
        self.bin = subprocess.Popen(["./main"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
        self.marks = 0
        self.out_str = ""

    def run_command(self, inp, expected_out, marks):
        try:
            out, err = self.bin.communicate(input=inp)
            if MODE == "GENERATE":
                test.append((inp, out, 1))
            if(err != ""):
                self.out_str += "Error running command: {0}".format(err)
                return None
            if(out == expected_out):
                self.marks += marks
                self.out_str += "Test passed: {0}".format(inp)
            else:
                self.out_str += "Test failed: {0}".format(inp)
                self.out_str += "Expected: {0}".format(expected_out)
                self.out_str += "Got: {0}".format(out)
        except Exception as e:
            print("Error running command: {0}".format(e))
            return None

if __name__ == '__main__':
    missing_files = check_submitted_files(['main.cpp'])
    for path in missing_files:
        print('Missing {0}'.format(path))
    if len(missing_files) == 0:
        print('All required files submitted!')
        print('Running tests...')
        print('')
    else:
        print('Missing some required files!')
        exit(1)

    # subprocess.run(["rm", "-f", "main"], check=True)
    subprocess.run(["g++", "main.cpp", "-o", "main"], check=True)
 
    test_cases = []
    if MODE == "GENERATE":
        test_cases = generate_test_cases()
    else:
        with open("test_cases.txt", "r") as f:
            with open("output.txt", "r") as f2:
                # read one line from test_cases.txt
                for t in range(10):
                    test_case = f.readline()
                    # read 111 lines from output.txt
                    expected_out = ''
                    for i in range(111):
                        expected_out += f2.readline()
                    test_cases.append((test_case, expected_out, 1))

        

    total_marks = 0

    for test_case in test_cases:
        tester = Tester()
        # print("Running test case: {0}".format(test_case))
        tester.run_command(test_case[0], test_case[1], test_case[2])
        print(tester.out_str)
        total_marks += tester.marks

    if MODE == "GENERATE":
        print("Generated {0} test cases".format(len(test)))
        print("Writing to test_cases.txt...")
        with open("test_cases.txt", "w") as f:
            with open("output.txt", "w") as f2:
                for test_case in test:
                    f.write("{0}\n".format(test_case[0]))
                    f2.write("{0}".format(test_case[1]))
        print("Done")

    print("Total marks: {0}".format(total_marks))