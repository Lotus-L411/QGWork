package main;

import dao.StudentDao;
import model.Student;
import model.User;
import service.AdminService;
import service.AuthService;
import service.StudentService;

import java.sql.SQLException;
import java.util.Scanner;


public class login_register {
    private static Scanner sc = new Scanner(System.in);
    private static AuthService authService = new AuthService();
    private static StudentService studentService = new StudentService();
    private static AdminService adminService = new AdminService();
    private static StudentDao studentDao = new StudentDao();

    public static void main(String[] args) throws SQLException {
        while (true) {
            System.out.println("===========================");
            System.out.println(" 学生选课管理系统");
            System.out.println("===========================");
            System.out.println("1. 登录");
            System.out.println("2. 注册");
            System.out.println("3. 退出");
            System.out.print("请选择操作（输入 1-3）：");

            int choice = sc.nextInt();
            sc.nextLine(); // 清除缓冲区

            switch (choice) {
                case 1:
                    login();
                    break;
                case 2:
                    register();
                    break;
                case 3:
                    System.out.println("退出系统。");
                    return;
                default:
                    System.out.println("无效选择，请重新输入！");
            }
        }
    }

    /**
     * 用户登录
     */
    private static void login() throws SQLException {
        System.out.print("请输入用户名：");
        String username = sc.nextLine();
        System.out.print("请输入密码：");
        String password = sc.nextLine();

        User user = authService.login(username, password);
        if (user != null) {
            System.out.println("登录成功！你的角色是：" + user.getRole());
            if (user.getRole().equals("STUDENT")) {
                Student student = studentDao.findByname(username);
                studentService.showstudentMenu(student.getId());
            }else {
                adminService.showadminMenu();
            }
        } else {
            System.out.println("用户名或密码错误！");
        }
    }

    /**
     * 用户注册
     */
    private static void register() {
        System.out.println("===== 用户注册 =====");
        System.out.print("请输入用户名：");
        String username = sc.nextLine();
        System.out.print("请输入密码：");
        String password = sc.nextLine();
        System.out.print("请确认密码：");
        String confirmPassword = sc.nextLine();
        System.out.print("请选择角色（输入 1 代表学生，2 代表管理员）：");
        int roleChoice = sc.nextInt();
        sc.nextLine(); // 清除缓冲区

        // 验证密码是否一致
        if (!password.equals(confirmPassword)) {
            System.out.println("密码不一致，请重新注册！");
            return;
        }

        String role = (roleChoice == 1) ? "STUDENT" : "ADMIN";

        if (authService.register(username, password, role)) {
            System.out.println("注册成功！");
        } else {
            System.out.println("注册失败，请重试！");
        }
    }
}
