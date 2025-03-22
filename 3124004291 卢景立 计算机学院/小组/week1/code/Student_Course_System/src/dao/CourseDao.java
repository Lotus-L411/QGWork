package dao;

import model.Course;
import util.DBUtil;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class CourseDao {
    public List<Course> findAll() {
        List<Course> courses = new ArrayList<>();
        String sql = "SELECT * FROM courses";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                Course course = new Course();
                course.setId(rs.getInt("id"));
                course.setName(rs.getString("name"));
                course.setCredit(rs.getInt("credit"));

                // 从数据库读取日期并转换为 LocalDate
                course.setStartDate(rs.getDate("start_date").toLocalDate());
                course.setEndDate(rs.getDate("end_date").toLocalDate());

                courses.add(course);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return courses;
    }

    public boolean updateCredit(int courseId, int credit) {
        String sql = "UPDATE courses SET credit = ? WHERE id = ?";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, credit);
            stmt.setInt(2, courseId);
            int rows = stmt.executeUpdate();
            return rows > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public boolean insertCourse(String name, int credit, LocalDate start_date, LocalDate end_date) {
        String sql = "INSERT INTO courses (name, credit, start_date, end_date) VALUES (?, ?, ?, ?)";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, name);
            stmt.setInt(2, credit);
            stmt.setDate(3, Date.valueOf(start_date));
            stmt.setDate(4, Date.valueOf(end_date));
            int rows = stmt.executeUpdate();
            return rows > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}