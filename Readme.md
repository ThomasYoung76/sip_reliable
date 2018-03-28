# 楼宇通信可靠性测试
---

## 用法：
	执行test_thread.sh文件，含两个参数，第二个参数固定位reliability，表示执行可靠性用例

	如：./test_thread.sh reg_thread reliability

## 参数：
	reg_thread: test_reg_thread.cpp测试用例文件名的一部分，表示编译该文件
	reliability： 可靠性测试。常规测试不需要这个参数

## 功能：
	a)利用test_call.mk生成新的makefile文件，然后重新编译（执行make clean和make）
	b)将编译后生成的可执行文件拷贝到NFS共享目录

## 文件用途
	test_reg.cpp：单线程注册1000台梯口机，配合test.sh使用
	test_reg_thread.cpp：4个线程死循环注册1000台梯口机，配合test_thread.sh使用
	TestForReliability.cpp：被引用的文件，继承UserAgent类
	TestForReliability.h：被引用的文件，继承UserAgent类
	test_thread.sh: 批处理shell文件