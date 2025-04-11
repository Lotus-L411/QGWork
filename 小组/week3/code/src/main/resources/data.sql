-- 初始化角色
INSERT INTO roles(name) VALUES('ROLE_USER');
INSERT INTO roles(name) VALUES('ROLE_ADMIN');

-- 初始化课程
INSERT INTO courses(title, description, instructor, duration, price) 
VALUES('Java Programming', 'Learn Java from scratch', 'John Doe', 40, 199.99);

INSERT INTO courses(title, description, instructor, duration, price) 
VALUES('Spring Boot', 'Master Spring Boot framework', 'Jane Smith', 30, 149.99);

INSERT INTO courses(title, description, instructor, duration, price) 
VALUES('Vue.js', 'Build modern web applications with Vue', 'Mike Johnson', 25, 129.99);