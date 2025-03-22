package model;

import java.time.LocalDate;

public class Course {
    private int id;
    private String name;
    private int credit;
    private LocalDate startDate; // 使用 LocalDate 表示开始日期
    private LocalDate endDate;   // 使用 LocalDate 表示结束日期

    public Course() {
    }

    public Course(int id, String name, LocalDate startDate, int credit, LocalDate endDate) {
        this.id = id;
        this.name = name;
        this.startDate = startDate;
        this.credit = credit;
        this.endDate = endDate;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public LocalDate getStartDate() {
        return startDate;
    }

    public void setStartDate(LocalDate startDate) {
        this.startDate = startDate;
    }

    public int getCredit() {
        return credit;
    }

    public void setCredit(int credit) {
        this.credit = credit;
    }

    public LocalDate getEndDate() {
        return endDate;
    }

    public void setEndDate(LocalDate endDate) {
        this.endDate = endDate;
    }
}