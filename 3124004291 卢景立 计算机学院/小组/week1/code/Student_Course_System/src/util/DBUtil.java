package util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import static java.lang.Class.forName;

public class DBUtil {
    // JDBC URL，添加 serverTimezone 参数
    private static final String URL = "jdbc:mysql://localhost:3306/student_course_system?serverTimezone=UTC";
    private static final String USER = "root"; // 数据库用户名
    private static final String PASSWORD = "123456"; // 数据库密码

    //    static {
    //        try {
    //            // 加载 MySQL
    //            Class.forName("com.mysql.cj.jdbc.Driver");
    //            System.out.println("MySQL 驱动加载成功！");
    //        } catch (ClassNotFoundException e) {
    //            System.out.println("MySQL 驱动加载失败！");
    //            e.printStackTrace();
    //        }
    //    }

    /**
     * 获取数据库连接
     *
     * @return 数据库连接对象
     * @throws SQLException 如果连接失败
     */
    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(URL, USER, PASSWORD);
    }
}