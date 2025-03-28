<template>
  <div class="auth-container">
    <div class="auth-card">
      <div class="auth-header">
        <h1>{{ isLogin ? '用户登录' : '用户注册' }}</h1>
        <p>{{ isLogin ? '欢迎回来，请输入您的账号密码' : '创建新账号，加入我们' }}</p>
      </div>

      <form @submit.prevent="handleSubmit" class="auth-form">
        <!-- 邮箱输入 -->
        <div class="form-group">
          <label for="email">邮箱</label>
          <input
            type="email"
            id="email"
            v-model="form.email"
            @blur="validateField('email')"
            placeholder="请输入邮箱"
          />
          <span class="error-message" v-if="errors.email">{{ errors.email }}</span>
        </div>

        <!-- 手机号输入 (仅注册时显示) -->
        <div class="form-group" v-if="!isLogin">
          <label for="phone">手机号</label>
          <input
            type="tel"
            id="phone"
            v-model="form.phone"
            @blur="validateField('phone')"
            placeholder="请输入手机号"
          />
          <span class="error-message" v-if="errors.phone">{{ errors.phone }}</span>
        </div>

        <!-- 密码输入 -->
        <div class="form-group">
          <label for="password">密码</label>
          <input
            type="password"
            id="password"
            v-model="form.password"
            @blur="validateField('password')"
            placeholder="请输入密码"
          />
          <span class="error-message" v-if="errors.password">{{ errors.password }}</span>
        </div>

        <!-- 确认密码 (仅注册时显示) -->
        <div class="form-group" v-if="!isLogin">
          <label for="confirmPassword">确认密码</label>
          <input
            type="password"
            id="confirmPassword"
            v-model="form.confirmPassword"
            @blur="validateField('confirmPassword')"
            placeholder="请再次输入密码"
          />
          <span class="error-message" v-if="errors.confirmPassword">{{ errors.confirmPassword }}</span>
        </div>

        <button type="submit" class="submit-btn">
          {{ isLogin ? '登录' : '注册' }}
        </button>
      </form>

      <div class="auth-footer">
        <p>
          {{ isLogin ? '没有账号？' : '已有账号？' }}
          <a href="#" @click.prevent="toggleAuthMode">{{ isLogin ? '立即注册' : '立即登录' }}</a>
        </p>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      isLogin: true,
      form: {
        email: '',
        phone: '',
        password: '',
        confirmPassword: ''
      },
      errors: {
        email: '',
        phone: '',
        password: '',
        confirmPassword: ''
      }
    }
  },
  methods: {
    toggleAuthMode() {
      this.isLogin = !this.isLogin
      // 重置表单和错误
      Object.keys(this.form).forEach(key => this.form[key] = '')
      Object.keys(this.errors).forEach(key => this.errors[key] = '')
    },
    validateField(field) {
      if (field === 'email') {
        if (!this.form.email) {
          this.errors.email = '邮箱不能为空'
        } else if (!/^\w+([.-]?\w+)*@\w+([.-]?\w+)*(\.\w{2,3})+$/.test(this.form.email)) {
          this.errors.email = '请输入有效的邮箱地址'
        } else {
          this.errors.email = ''
        }
      }

      if (field === 'phone' && !this.isLogin) {
        if (!this.form.phone) {
          this.errors.phone = '手机号不能为空'
        } else if (!/^1[3-9]\d{9}$/.test(this.form.phone)) {
          this.errors.phone = '请输入有效的手机号'
        } else {
          this.errors.phone = ''
        }
      }

      if (field === 'password') {
        if (!this.form.password) {
          this.errors.password = '密码不能为空'
        } else if (this.form.password.length < 6) {
          this.errors.password = '密码长度不能少于6位'
        } else {
          this.errors.password = ''
        }
      }

      if (field === 'confirmPassword' && !this.isLogin) {
        if (!this.form.confirmPassword) {
          this.errors.confirmPassword = '请确认密码'
        } else if (this.form.password !== this.form.confirmPassword) {
          this.errors.confirmPassword = '两次输入的密码不一致'
        } else {
          this.errors.confirmPassword = ''
        }
      }
    },
    validateForm() {
      this.validateField('email')
      this.validateField('password')
      if (!this.isLogin) {
        this.validateField('phone')
        this.validateField('confirmPassword')
      }
      
      return !Object.values(this.errors).some(error => error) && 
             (this.isLogin ? this.form.email && this.form.password : 
                             this.form.email && this.form.phone && this.form.password && this.form.confirmPassword)
    },
    handleSubmit() {
      if (this.validateForm()) {
        alert(this.isLogin ? '登录成功!' : '注册成功!')
        // 这里可以添加实际的提交逻辑
      } else {
        console.log('表单验证失败')
      }
    }
  }
}
</script>

<style scoped>
.auth-container {
  display: flex;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
  background-color: #f5f7fa;
  font-family: 'Arial', sans-serif;
}

.auth-card {
  width: 100%;
  max-width: 400px;
  background: white;
  border-radius: 10px;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
  padding: 2rem;
  transition: all 0.3s ease;
}

.auth-header {
  text-align: center;
  margin-bottom: 2rem;
}

.auth-header h1 {
  color: #333;
  font-size: 1.8rem;
  margin-bottom: 0.5rem;
}

.auth-header p {
  color: #666;
  font-size: 0.9rem;
}

.auth-form {
  display: flex;
  flex-direction: column;
  gap: 1.2rem;
}

.form-group {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
}

.form-group label {
  font-size: 0.9rem;
  color: #555;
  font-weight: 500;
}

.form-group input {
  padding: 0.8rem 1rem;
  border: 1px solid #ddd;
  border-radius: 6px;
  font-size: 0.95rem;
  transition: border 0.3s;
}

.form-group input:focus {
  outline: none;
  border-color: #4a90e2;
  box-shadow: 0 0 0 2px rgba(74, 144, 226, 0.2);
}

.error-message {
  color: #e74c3c;
  font-size: 0.8rem;
  height: 1rem;
}

.submit-btn {
  background-color: #4a90e2;
  color: white;
  border: none;
  padding: 0.8rem;
  border-radius: 6px;
  font-size: 1rem;
  font-weight: 500;
  cursor: pointer;
  transition: background-color 0.3s;
  margin-top: 0.5rem;
}

.submit-btn:hover {
  background-color: #3a7bc8;
}

.auth-footer {
  text-align: center;
  margin-top: 1.5rem;
  font-size: 0.9rem;
  color: #666;
}

.auth-footer a {
  color: #4a90e2;
  text-decoration: none;
  font-weight: 500;
}

.auth-footer a:hover {
  text-decoration: underline;
}
</style>