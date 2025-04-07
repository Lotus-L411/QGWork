package service;

import dao.UserDao;
import model.User;

/**
 * 认证服务类，负责用户登录和注册
 */
public class AuthService {
    private UserDao userDao = new UserDao();

    /**
     * 用户登录
     *
     * @param username 用户名
     * @param password 密码
     * @return 登录成功的用户对象，失败返回 null
     */
    public User login(String username, String password) {
        User user = userDao.findByUsername(username);
        if (user != null && user.getPassword().equals(password)) {
            return user;
        }

        return null;
    }

    /**
     * 用户注册
     *
     * @param username 用户名
     * @param password 密码
     * @param role     角色
     * @return 是否注册成功
     */
    public boolean register(String username, String password, String role) {
        return userDao.register(username, password, role);
    }
}
