package model;

/**
 * 学生实体类，对应 students 表
 */
public class Student {
    private int id; // 学生ID
    private int userId; // 关联 users 表
    private String name; // 学生姓名
    private String phone; // 学生手机号

    // 构造方法
    public Student() {}

    public Student(int id, int userId, String name, String phone) {
        this.id = id;
        this.userId = userId;
        this.name = name;
        this.phone = phone;
    }

    // Getter 和 Setter 方法
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getUserId() {
        return userId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }
}