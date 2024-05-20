#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "BookingScheduler.cpp"

TEST(BookingSchedulerTest, 예약은_정시에만_가능하다_정시가_아닌경우_예약불가) {
	BookingScheduler bookingScheduler{ 10 };
	tm time{};
	time.tm_hour = 8;
	time.tm_min = 30;

	Customer customer{ "CUSTOMER_NAME", "+82-10-1234-4567" };
	Schedule schedule{ time, 2, customer };
	EXPECT_THROW(bookingScheduler.addSchedule(&schedule), std::exception);
}

TEST(BookingSchedulerTest, 예약은_정시에만_가능하다_정시인_경우_예약가능) {
	BookingScheduler bookingScheduler{ 10 };
	tm time{};
	time.tm_hour = 8;
	time.tm_min = 0;

	Customer customer{ "CUSTOMER_NAME", "+82-10-1234-4567" };
	Schedule schedule{ time, 2, customer };
	bookingScheduler.addSchedule(&schedule);
}

TEST(BookingSchedulerTest, 시간대별_인원제한이_있다_같은_시간대에_Capacity_초과할_경우_예외발생) {
	BookingScheduler bookingScheduler{ 10 };
	tm time{};
	time.tm_hour = 8;
	time.tm_min = 0;

	Customer customer{ "CUSTOMER_NAME", "+82-10-1234-4567" };
	Schedule schedule1{ time, 10, customer };
	Schedule schedule2{ time, 1, customer };
	bookingScheduler.addSchedule(&schedule1);
	EXPECT_THROW(bookingScheduler.addSchedule(&schedule2), std::exception);
}

TEST(BookingSchedulerTest, 시간대별_인원제한이_있다_같은_시간대가_다르면_Capacity_차있어도_스케쥴_추가_성공) {

}

TEST(BookingSchedulerTest, 예약완료시_SMS는_무조건_발송) {

}

TEST(BookingSchedulerTest, 이메일이_없는_경우에는_이메일_미발송) {

}

TEST(BookingSchedulerTest, 이메일이_있는_경우에는_이메일_발송) {

}

TEST(BookingSchedulerTest, 현재날짜가_일요일인_경우_예약불가_예외처리) {

}

TEST(BookingSchedulerTest, 현재날짜가_일요일이_아닌경우_예약가능) {

}