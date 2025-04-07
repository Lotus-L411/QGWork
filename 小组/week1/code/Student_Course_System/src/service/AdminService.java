package service;

import dao.CourseDao;
import dao.StudentCourseDao;
import dao.StudentDao;
import model.Course;
import model.Student;
import java.time.LocalDate;
import java.util.List;
import java.util.Scanner;

public class AdminService {
    private StudentDao studentDao = new StudentDao();
    private CourseDao courseDao = new CourseDao();
    private StudentCourseDao studentCourseDao = new StudentCourseDao();
    private Scanner sc = new Scanner(System.in);

    public void showadminMenu() {
        while (true) {
            System.out.println("===== 管理员菜单 =====");
            System.out.println("1. 查询所有学生");
            System.out.println("2. 修改学生手机号");
            System.out.println("3. 查询所有课程");
            System.out.println("4. 修改课程学分");
            System.out.println("5. 查询某课程的学生名单");
            System.out.println("6. 查询某学生的选课情况");
            System.out.println("7. 添加课程");
            System.out.println("8. 退出");
            System.out.print("请选择操作（输入 1-8）：");

            int choice = sc.nextInt();
            sc.nextLine(); // 清除缓冲区

            switch (choice) {
                case 1:
                    showAllStudents();
                    break;
                case 2:
                    updateStudentPhone();
                    break;
                case 3:
                    showAllCourses();
                    break;
                case 4:
                    updateCourseCredit();
                    break;
                case 5:
                    showStudentsByCourse();
                    break;
                case 6:
                    showCoursesByStudent();
                    break;
                case 7:
                    AddCourse();
                    break;
                case 8:
                    System.out.println("退出成功");
                    return;
                default:
                    System.out.println("无效选择，请重新输入！");
            }
        }
    }

    private void showAllStudents() {
        List<Student> students = studentDao.findAll();
        if (students.isEmpty()) {
            System.out.println("暂无学生注册~~~~~");
            return;
        }
        System.out.println("===== 所有学生 =====");
        for (Student student : students) {
            System.out.println("ID: " + student.getId() + ", 姓名: " + student.getName() + ", 手机号: " + student.getPhone());
        }
    }

    private void updateStudentPhone() {
        System.out.print("请输入学生ID：");
        int studentId = sc.nextInt();
        sc.nextLine(); // 清除缓冲区
        System.out.print("请输入新手机号：");
        String phone = sc.nextLine();

        if (studentDao.updatePhone(studentId, phone)) {
            System.out.println("手机号更新成功！");
        } else {
            System.out.println("手机号更新失败，请重试！");
        }
    }

    private void showAllCourses() {
        List<Course> courses = courseDao.findAll();
        if (courses.isEmpty()) {
            System.out.println("暂无课程，请先添加课程~~~~~");
            return;
        }
        System.out.println("===== 所有课程 =====");
        for (Course course : courses) {
            System.out.println("ID: " + course.getId() + ", 名称: " + course.getName() + ", 学分: " + course.getCredit());
        }
    }

    private void updateCourseCredit() {
        System.out.print("请输入课程ID：");
        int courseId = sc.nextInt();
        sc.nextLine(); // 清除缓冲区
        System.out.print("请输入新学分：");
        int credit = sc.nextInt();
        sc.nextLine(); // 清除缓冲区

        if (courseDao.updateCredit(courseId, credit)) {
            System.out.println("课程学分更新成功！");
        } else {
            System.out.println("课程学分更新失败，请重试！");
        }
    }

    private void showStudentsByCourse() {
        System.out.print("请输入课程ID：");
        int courseId = sc.nextInt();
        sc.nextLine(); // 清除缓冲区

        List<Student> students = studentCourseDao.findStudentsByCourseId(courseId);
        if (students.isEmpty()) {
            System.out.println("暂无学生选该课程~~~~~");
            return;
        }
        System.out.println("===== 课程学生名单 =====");
        for (Student student : students) {
            System.out.println("ID: " + student.getId() + ", 姓名: " + student.getName() + ", 手机号: " + student.getPhone());
        }
    }

    private void showCoursesByStudent() {
        System.out.print("请输入学生ID：");
        int studentId = sc.nextInt();
        sc.nextLine(); // 清除缓冲区

        List<Course> courses = studentCourseDao.findCoursesByStudentId(studentId);
        if (courses.isEmpty()) {
            System.out.println("该学生还未选任何课程~~~~~");
            return;
        }
        System.out.println("===== 学生选课情况 =====");
        for (Course course : courses) {
            System.out.println("ID: " + course.getId() + ", 名称: " + course.getName() + ", 学分: " + course.getCredit());
        }


    }

    private void AddCourse() {
        System.out.print("请输入课程名称：");
        String coursename = sc.next();
        sc.nextLine(); // 清除缓冲区
        System.out.print("请输入课程学分：");
        int credit = sc.nextInt();
        sc.nextLine(); // 清除缓冲区
        System.out.print("请输入课程开始时间(如：2024-04-11)：");
        String dateInput = sc.next();
        LocalDate course_start_date = LocalDate.parse(dateInput);
        sc.nextLine(); // 清除缓冲区
        System.out.print("请输入课程结束时间(如：2025-04-11)：");
        String dateEnd = sc.next();
        LocalDate course_end_date = LocalDate.parse(dateEnd);
        sc.nextLine(); // 清除缓冲区
        if(courseDao.insertCourse(coursename, credit, course_start_date, course_end_date)) {
            System.out.println("添加成功");
        }else {
            System.out.println("添加失败，请重试");
        }
    }
}
