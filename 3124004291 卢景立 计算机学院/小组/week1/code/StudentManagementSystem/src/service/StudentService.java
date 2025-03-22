package service;

import dao.CourseDao;
import dao.StudentCourseDao;
import dao.StudentDao;
import model.Course;


import java.util.List;
import java.util.Scanner;

public class StudentService {
    private CourseDao courseDao = new CourseDao();
    private StudentCourseDao studentCourseDao = new StudentCourseDao();
    private Scanner sc = new Scanner(System.in);
    private StudentDao studentDao = new StudentDao();

    public void showstudentMenu(int studentId) {
        while (true) {
            System.out.println("===== 学生菜单 =====");
            System.out.println("1. 查看可选课程");
            System.out.println("2. 选择课程");
            System.out.println("3. 退选课程");
            System.out.println("4. 查看已选课程");
            System.out.println("5. 修改手机号");
            System.out.println("6. 退出");
            System.out.print("请选择操作（输入 1-6）：");

            int choice = sc.nextInt();
            sc.nextLine(); // 清除缓冲区

            switch (choice) {
                case 1:
                    showAvailableCourses();
                    break;
                case 2:
                    selectCourse(studentId);
                    break;
                case 3:
                    dropCourse(studentId);
                    break;
                case 4:
                    showSelectedCourses(studentId);
                    break;
                case 5:
                    updatephone(studentId);
                    break;
                case 6:
                    System.out.println("退出学生菜单。");
                    return;
                default:
                    System.out.println("无效选择，请重新输入！");
            }
        }
    }

    private void showAvailableCourses() {
        List<Course> courses = courseDao.findAll();
        if (courses.isEmpty()) {
            System.out.println("暂无课程可选~~~~~");
            return;
        }
        System.out.println("===== 可选课程 =====");
        for (Course course : courses) {
            System.out.println(course.getId() + ". " + course.getName() +
                    " (" + course.getCredit() + " 学分) - " +
                    "开始日期: " + course.getStartDate() +
                    ", 结束日期: " + course.getEndDate());
        }
    }

    private void selectCourse(int studentId) {
        System.out.print("请输入要选择的课程ID：");
        int courseId = sc.nextInt();
        sc.nextLine(); // 清除缓冲区

        if (studentCourseDao.AddCourse(studentId, courseId)) {
            System.out.println("选课成功！");
        } else {
            System.out.println("选课失败，请重试！");
        }
    }

    private void dropCourse(int studentId) {
        System.out.print("请输入要退选的课程ID：");
        int courseId = sc.nextInt();
        sc.nextLine(); // 清除缓冲区

        if (studentCourseDao.DropCourse(studentId, courseId)) {
            System.out.println("退选成功！");
        } else {
            System.out.println("退选失败，请重试！");
        }
    }

    private void showSelectedCourses(int studentId) {
        List<Course> courses = studentCourseDao.findCoursesByStudentId(studentId);
        if (courses.isEmpty()) {
            System.out.println("还未选择任何课程，请前面选课~~~~~");
            return;
        }
        System.out.println("===== 已选课程 =====");
        for (Course course : courses) {
            System.out.println(course.getId() + ". " + course.getName() +
                    " (" + course.getCredit() + " 学分) - " +
                    "开始日期: " + course.getStartDate() +
                    ", 结束日期: " + course.getEndDate());
        }
    }

    private void updatephone(int studentId) {
        System.out.print("请输入新手机号：");
        String phone = sc.nextLine();

        // 调用 DAO 更新手机号

        if (studentDao.updatePhone(studentId,phone)) {
            System.out.println("手机号更新成功！");
        } else {
            System.out.println("手机号更新失败，请重试！");
        }

    }
}
