#include <iostream>
#include <windows.h>

#include "model.h"
#include "control.h"
#include "view.h"

int main() {

	/// 독서실 생성, 좌석 세팅
	StudyRoom E7("E7", 11);
	Pos temp_pos(0, 0);
	E7.add_seat(Seat(&E7, 1, temp_pos));
	temp_pos(1, 0);
	E7.add_seat(Seat(&E7, 2, temp_pos));
	temp_pos(2, 0);
	E7.add_seat(Seat(&E7, 3, temp_pos));
	temp_pos(3, 0);
	E7.add_seat(Seat(&E7, 4, temp_pos));
	temp_pos(0, 1);
	E7.add_seat(Seat(&E7, 5, temp_pos));
	temp_pos(1, 1);
	E7.add_seat(Seat(&E7, 6, temp_pos));
	temp_pos(2, 1);
	E7.add_seat(Seat(&E7, 7, temp_pos));
	temp_pos(3, 1);
	E7.add_seat(Seat(&E7, 8, temp_pos));
	temp_pos(1, 3);
	E7.add_seat(Seat(&E7, 9, temp_pos));
	temp_pos(2, 3);
	E7.add_seat(Seat(&E7, 10, temp_pos));
	temp_pos(3, 3);
	E7.add_seat(Seat(&E7, 11, temp_pos));

	UI main_interface;

	StudentDB database;
	StudyRoomDB room_database;

	database.load_student_admin_database();
	database.load_student_database();
	room_database.load_studyroom_database();

	LogIn log_in;
	ControlByStudent cs;
	ControlByAdmin ca;
	
	system("cls");

	while (true) {
		system("cls");
		int sel;
		std::cout << "\n\n--------------------     독서실 통합 관리 프로그램     --------------------" << std::endl;
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "1. 학생 로그인     2. 관리자 로그인     3.학생 회원가입     4.관리자 회원가입     5. 종료" << "\n\n입력: ";
		std::cin >> sel;
		if (std::cin.fail() || sel < 1 || sel > 5) {
			std::cout << "\n\n잘못된 입력입니다";
			Sleep(500);
			std::cin.clear();
			std::cin.ignore(100, '\n');
			system("cls");
			continue;
		}
		else if (sel == 1) {
			system("cls");
			if (!log_in.student_log_in(&database, &cs)) {
				continue;
			}
			while (true) {
				system("cls");
				int sel;
				std::cout << "\n\nUser: " << cs.get_student()->get_student_num() << std::endl << std::endl;
				if (cs.get_student()->get_is_using()) {
					std::cout << "현재 " << cs.get_student()->get_studyroom_using()->get_name() << "독서실의 " << cs.get_student()->get_seat_using()->get_seat_num() << "번 좌석을 예약중입니다.\n\n";
				}
				std::cout << "\n\n1. 독서실 선택     2. 로그아웃\n\n";
				std::cout << "입력: ";
				std::cin >> sel;
				if (std::cin.fail() || sel < 1 || sel > 2) {
					std::cout << "\n\n잘못된 입력입니다";
					Sleep(500);
					std::cin.clear();
					std::cin.ignore(100, '\n');
					system("cls");
					continue;
				}
				else if (sel == 1) {
					system("cls");
					std::cout << "\n\n1. E7     2. 뒤로 가기\n\n입력: ";
					std::cin >> sel;
					if (std::cin.fail() || sel < 1 || sel > 2) {
						std::cout << "\n\n잘못된 입력입니다";
						Sleep(500);
						std::cin.clear();
						std::cin.ignore(100, '\n');
						system("cls");
						continue;
					}
					else if (sel == 1) {
						cs.get_student()->set_studyroom_using(&E7);
						while (true) {
							system("cls");
							std::cout << "\n\n현재 선택한 독서실: E7\n\n";
							main_interface.show_studyroom(&E7);
							std::cout << "\n\n1. 예약     2. 예약 취소     3. 좌석 정보 확인     4. 뒤로 가기\n\n입력: ";
							std::cin >> sel;
							if (std::cin.fail() || sel < 1 || sel > 4) {
								std::cout << "\n\n잘못된 입력입니다";
								Sleep(500);
								std::cin.clear();
								std::cin.ignore(100, '\n');
								system("cls");
								continue;
							}
							else if (sel == 1) {
								if (cs.get_student()->get_is_using()) {
									std::cout << "\n\n이미 좌석을 예약중입니다.";
									Sleep(500);
									continue;
								}
								int seat_sel;
								std::cout << "\n\n예약할 좌석의 번호를 입력하십시오: ";
								std::cin >> seat_sel;
								
								if (std::cin.fail() || seat_sel < 1 || seat_sel > cs.get_student()->get_studyroom_using()->get_max_seat_num()) {
									std::cout << "\n\n잘못된 입력입니다.";
									std::cin.clear();
									std::cin.ignore(100, '\n');
									Sleep(500);
									continue;
								}
								cs.make_reservation(cs.get_student()->get_studyroom_using()->get_seat(seat_sel - 1));
								std::cout << "\n\n예약이 완료되었습니다.";
								Sleep(500);
								continue;
							}
							else if (sel == 2) {
								std::string check_pwd;
								if (!cs.get_student()->get_is_using()) {
									std::cout << "\n\n현재 예약중인 좌석이 없습니다.";
									Sleep(500);
									continue;
								}
								std::cout << "\n\n비밀번호를 입력해 주십시오: ";
								std::cin >> check_pwd;
								if (check_pwd != cs.get_student()->get_password()) {
									std::cout << "\n\n잘못된 비밀번호입니다.";
									Sleep(500);
									continue;
								}
								cs.cancel_reservation();
							}
							else if (sel == 3) {
								int seat_sel;
								std::cout << "\n\n좌석 번호를 입력해 주십시오: ";
								std::cin >> seat_sel;
								if (std::cin.fail() || seat_sel < 1 || seat_sel > cs.get_student()->get_studyroom_using()->get_max_seat_num()) {
									std::cout << "\n\n잘못된 입력입니다.";
									std::cin.clear();
									std::cin.ignore(100, '\n');
									Sleep(500);
									continue;
								}
								while (true) {
									system("cls");
									main_interface.show_seat_status(cs.get_student()->get_studyroom_using()->get_seat(seat_sel - 1));
									std::cout << "\n\n1. 뒤로 가기\n\n입력: ";
									std::cin >> sel;
									if (std::cin.fail() || seat_sel < 1 || seat_sel > cs.get_student()->get_studyroom_using()->get_max_seat_num()) {
										std::cout << "\n\n잘못된 입력입니다.";
										std::cin.clear();
										std::cin.ignore(100, '\n');
										Sleep(500);
										continue;
									}
									if (sel == 1) {
										break;
									}
								}
							}
							else {
								break;
							}
						}
					}
					else {
						continue;
					}
				}
				else if (sel == 2) {
					cs.set_student(nullptr);
					break;
				}
			}
		}
		else if (sel == 2) {
			system("cls");
			if (!log_in.admin_log_in(&database, &ca)) {
				continue;
			}
			while (true) {
				system("cls");
				std::cout << "\n\n1. 독서실 선택     2. 로그아웃\n\n";
				std::cout << "입력: ";
				std::cin >> sel;
				if (std::cin.fail() || sel < 1 || sel > 2) {
					std::cout << "\n\n잘못된 입력입니다";
					Sleep(500);
					std::cin.clear();
					std::cin.ignore(100, '\n');
					system("cls");
					continue;
				}
				else if (sel == 1) {
					while (true) {
						system("cls");
						std::cout << "\n\n1. E7     2. 뒤로 가기\n\n입력: ";
						std::cin >> sel;
						if (std::cin.fail() || sel < 1 || sel > 2) {
							std::cout << "\n\n잘못된 입력입니다";
							Sleep(500);
							std::cin.clear();
							std::cin.ignore(100, '\n');
							system("cls");
							continue;
						}
						else if (sel == 1) {
							while (true) {
								system("cls");
								ca.get_admin()->set_studyroom_using(&E7);
								main_interface.show_studyroom(ca.get_admin()->get_studyroom_using());
								std::cout << "\n\n관리자는 좌석 확인과 좌석 예약 강제 취소만 가능합니다.\n\n1. 좌석 확인     2. 예약 강제 취소     3. 로그아웃\n\n입력: ";
								std::cin >> sel;
								if (std::cin.fail() || sel < 1 || sel > 3) {
									std::cout << "\n\n잘못된 입력입니다.";
									std::cin.clear();
									std::cin.ignore(100, '\n');
									Sleep(500);
									continue;
								}
								else if (sel == 1) {
									int seat_sel;
									std::cout << "\n\n좌석 번호를 입력해 주십시오: ";
									std::cin >> seat_sel;
									if (std::cin.fail() || seat_sel < 1 || seat_sel > ca.get_admin()->get_studyroom_using()->get_max_seat_num()) {
										std::cout << "\n\n잘못된 입력입니다.";
										std::cin.clear();
										std::cin.ignore(100, '\n');
										Sleep(500);
										continue;
									}
									while (true) {
										system("cls");
										main_interface.show_seat_status(ca.get_admin()->get_studyroom_using()->get_seat(seat_sel - 1));
										std::cout << "\n\n1. 뒤로 가기\n\n입력: ";
										std::cin >> sel;
										if (std::cin.fail() || seat_sel < 1 || seat_sel > ca.get_admin()->get_studyroom_using()->get_max_seat_num()) {
											std::cout << "\n\n잘못된 입력입니다.";
											std::cin.clear();
											std::cin.ignore(100, '\n');
											Sleep(500);
											continue;
										}
										if (sel == 1) {
											break;
										}
									}
								}
								else if (sel == 2) {
									int seat_sel;
									std::cout << "\n\n좌석 번호를 입력해 주십시오: ";
									std::cin >> seat_sel;
									if (std::cin.fail() || seat_sel < 1 || seat_sel > ca.get_admin()->get_studyroom_using()->get_max_seat_num()) {
										std::cout << "\n\n잘못된 입력입니다.";
										std::cin.clear();
										std::cin.ignore(100, '\n');
										Sleep(500);
										continue;
									}
									if (!ca.get_admin()->get_studyroom_using()->get_seat(seat_sel - 1)->is_reserved()) {
										std::cout << "\n\n예약되어 있지 않은 좌석입니다.";
										Sleep(500);
										continue;
									}
									ca.force_cancel_reservation(ca.get_admin()->get_studyroom_using()->get_seat(seat_sel - 1));
								}
								else {
									break;
								}
							}
						}
						else if (sel == 2) {
							break;
						}
					}
				}
				else if (sel == 2) {
					break;
				}
			}
		}
		else if (sel == 3) {
			system("cls");
			Register student_reg;
			student_reg.register_student(&database);
			Sleep(500);
		}
		else if (sel == 4) {
			system("cls");
			Register admin_reg;
			admin_reg.register_admin(&database);
			Sleep(500);
		}
		else if (sel == 4) {
			system("cls");
			std::cout << "2 선택" << std::endl;
			break;
		}
		else {
			std::cout << "프로그램을 종료합니다.";
			Sleep(1000);
			system("cls");
			break;
		}
	}

	database.save_student_admin_database();
	database.save_student_database();
	room_database.save_studyroom_database();

	return 0;
}