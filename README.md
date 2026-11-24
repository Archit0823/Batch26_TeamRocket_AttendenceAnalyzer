# 🎓 Attendance Eligibility Checker

A C program that checks whether students in the same class can achieve or maintain **75% attendance** by the end of the semester.

The program supports **at least 10 students** and calculates attendance separately for every subject.

## 📌 About the Project

Maintaining 75% attendance is a common requirement in colleges and universities.

This program helps students determine:

- Their current attendance percentage.
- Whether they currently have at least 75% attendance.
- Whether they can still reach 75% before the semester ends.
- How many remaining classes they must attend.
- How many remaining classes they can safely skip.
- Their maximum possible final attendance percentage.

The program also provides a summary of the entire class.

## ✨ Features

- Supports **1–10 subjects**.
- Supports **10–100 students** from the same class.
- Uses common class information for all students.
- Stores attendance information for every student.
- Validates numerical input.
- Calculates current attendance percentage.
- Calculates the minimum number of classes required to reach 75%.
- Calculates how many remaining classes can be skipped.
- Detects when reaching 75% is mathematically impossible.
- Displays the best possible final attendance.
- Provides a class-wide attendance summary.
- Allows individual student reports to be searched by name.
- Student-name searches are case-insensitive.

## 🧮 How It Works

For each subject:

```text
Current Attendance = (Classes Attended / Classes Held) × 100
```

The program then calculates whether 75% attendance can be achieved after considering the remaining classes.

```text
Final Classes = Classes Held + Classes Remaining
```

```text
Must Attend = ceil(0.75 × Final Classes) - Classes Already Attended
```

If the required number of classes is greater than the number of remaining classes, reaching 75% is not possible.

## 🟢 Attendance Status

The program gives one of three verdicts:

**SAFE** — The student currently has at least 75% attendance.

**AT RISK - can recover** — The student is currently below 75%, but can still reach it.

**CANNOT REACH 75%** — Even after attending every remaining class, the student cannot reach 75%.

## 💻 Program Flow

1. Enter the number of subjects.
2. Enter each subject's name.
3. Enter classes held and classes remaining.
4. Enter attendance details for each student.
5. Details for at least 10 students are collected.
6. Additional students can be added after the first 10.
7. A summary of all students is displayed.
8. Search for a student by name to see their detailed report.
9. Type `exit` to finish the program.

## 📊 Student Report

| Column | Meaning |
|---|---|
| Attended | Classes attended by the student |
| Held | Classes conducted so far |
| Remaining | Classes still left |
| Now | Current attendance percentage |
| Must Attend | Minimum remaining classes to attend |
| Can Skip | Remaining classes that can be skipped |
| Best Max | Maximum possible final attendance |
| Verdict | Attendance status |

## 🛠️ Requirements

A C compiler such as:

- GCC
- Clang
- MinGW
- Any IDE/compiler supporting C

## ▶️ Compile and Run

Compile using GCC:

```bash
gcc attandance_checker.c -o attandance_checker
```

### Windows

```bash
attandance_checker.exe
```

### Linux/macOS

```bash
./attandance_checker
```

## 📁 Project Structure

```text
Attendance-Eligibility-Checker/
│
├── attandance_checker.c
└── README.md
```

## 🎯 Concepts Used

This project demonstrates several fundamental C programming concepts:

- Functions
- Arrays
- Multidimensional arrays
- Loops
- Conditional statements
- Strings
- Input validation
- Mathematical calculations
- Formatted console output

## 👨‍💻 Language

**C**

## 📄 License

This project is intended for educational purposes.
