#include <iostream>
#include <windows.h>

#include "control.h"

// Register
void Register::register_student(StudentDB* db) {
	int st_num;
	std::string pwd;
	std::cout << "�й��� �Է��� �ּ���: ";
	std::cin >> st_num;
	std::cout << std::endl;
	if (db->get_student(st_num) != nullptr) {
		std::cout << "�̹� ��ϵ� �й��Դϴ�.";
		return;
	}
	std::cout << "��й�ȣ�� �Է��� �ּ���: ";
	std::cin >> pwd;
	std::cout << std::endl;
	db->add_student(Student(st_num, pwd));
	std::cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << std::endl;
}

void Register::register_admin(StudentDB* db) {
	std::string ad_id;
	std::string pwd;
	std::cout << "������ ID�� �Է��� �ּ���: ";
	std::cin >> ad_id;
	std::cout << std::endl;
	if (db->get_admin(ad_id) != nullptr) {
		std::cout << "�̹� ��ϵ� ID�Դϴ�.";
		return;
	}
	std::cout << "��й�ȣ�� �Է��� �ּ���: ";
	std::cin >> pwd;
	std::cout << std::endl;
	db->add_admin(Admin(ad_id, pwd));
	std::cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << std::endl;
}

// Log in
bool LogIn::student_log_in(StudentDB* db, ControlByStudent* control_student) {
	int st_num;
	std::string pwd;
	std::cout << "�й��� �Է��� �ּ���: ";
	std::cin >> st_num;
	std::cout << std::endl;

	Student* student = db->get_student(st_num);
	if (!student) {
		std::cout << "�������� �ʴ� �й��Դϴ�. ȸ������ �� ������ּ���." << std::endl;
		Sleep(500);
		return false;
	}

	std::cout << "��й�ȣ�� �Է��� �ּ���: ";
	std::cin >> pwd;
	std::cout << std::endl;

	if (pwd != student->get_password()) {
		std::cout << "��й�ȣ�� �߸��Ǿ����ϴ�." << std::endl;
		Sleep(500);
		return false;
	}

	std::cout << "�α��� �Ǿ����ϴ�." << std::endl;
	control_student->set_student(student);
	Sleep(500);
	return true;
}

bool LogIn::admin_log_in(StudentDB* db, ControlByAdmin* control_admin) {
	std::string ad_id;
	std::string pwd;
	std::cout << "������ ID�� �Է��� �ּ���: ";
	std::cin >> ad_id;
	std::cout << std::endl;

	Admin* admin = db->get_admin(ad_id);
	if (!admin) {
		std::cout << "��ϵ��� ���� ID�Դϴ�. ���α׷� �����ڿ��� �������ּ���." << std::endl;
		Sleep(500);
		return false;
	}

	std::cout << "��й�ȣ�� �Է��� �ּ���: ";
	std::cin >> pwd;
	std::cout << std::endl;

	if (pwd != admin->get_password()) {
		std::cout << "��й�ȣ�� �߸��Ǿ����ϴ�." << std::endl;
		Sleep(500);
		return false;
	}

	std::cout << "������ �������� �α��� �Ǿ����ϴ�." << std::endl;
	control_admin->set_admin(admin);
	Sleep(500);
	return true;
}

// ControlByStudent
void ControlByStudent::set_student(Student* controller) {
	student = controller;
}

Student* ControlByStudent::get_student() {
	return student;
}

void ControlByStudent::make_reservation(Seat* seat) {
	if (seat->is_reserved()) {
		std::cout << "�̹� ����� �¼��Դϴ�." << std::endl;
		return;
	}
	student->set_is_using_reverse();
	student->set_seat_using(seat);

	seat->set_reservation_reverse();
	seat->set_res_student(student);
	seat->get_belong_to()->set_cur_using_num(seat->get_belong_to()->get_cur_using_num() + 1);
}

void ControlByStudent::cancel_reservation() {
	if (!(student->get_is_using())) {
		std::cout << "�������� �¼��� �����ϴ�." << std::endl;
		return;
	}

	std::cout << std::endl << student->get_seat_using()->get_seat_num() << "�� �¼� ������ ��ҵǾ����ϴ�." << std::endl;

	student->get_seat_using()->get_belong_to()->set_cur_using_num(student->get_seat_using()->get_belong_to()->get_cur_using_num() - 1);
	student->set_is_using_reverse();
	student->get_seat_using()->set_res_student(nullptr);
	student->get_seat_using()->set_reservation_reverse();
	student->set_seat_using(nullptr);
	Sleep(500);
}

// ControlByAdmin
void ControlByAdmin::set_admin(Admin* controller) {
	admin = controller;
}

Admin* ControlByAdmin::get_admin() {
	return admin;
}

void ControlByAdmin::force_cancel_reservation(Seat* seat) {
	if (!(seat->is_reserved())) {
		std::cout << "�������� �¼��� �ƴմϴ�." << std::endl;
		return;
	}

	std::cout << seat->get_seat_num() << "�� �¼� ������ ��ҵǾ����ϴ�." << std::endl;
	seat->get_belong_to()->set_cur_using_num(seat->get_belong_to()->get_cur_using_num() - 1);
	seat->get_res_student()->set_is_using_reverse();
	seat->get_res_student()->set_seat_using(nullptr);
	seat->get_res_student()->set_studyroom_using(nullptr);

	seat->set_reservation_reverse();
	seat->set_res_student(nullptr);
	seat->set_away_from_reverse();

	Sleep(500);
}