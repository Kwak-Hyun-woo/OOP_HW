#pragma once

#include "model.h"

class Register {
public:
	void register_student(StudentDB* db);
	void register_admin(StudentDB* db);
};

class ControlByStudent {
private:
	Student* student = nullptr;
public:
	void set_student(Student* student);
	Student* get_student();
	void make_reservation(Seat* seat);			// 좌석 예약
	void cancel_reservation();					// 예약 취소
};

class ControlByAdmin : public ControlByStudent {
private:
	Admin* admin = nullptr;
public:
	void set_admin(Admin* admin);
	Admin* get_admin();
	void force_cancel_reservation(Seat* seat);
};

class LogIn {
public:
	bool student_log_in(StudentDB* db, ControlByStudent* control_student);
	bool admin_log_in(StudentDB* db, ControlByAdmin* control_admin);
};