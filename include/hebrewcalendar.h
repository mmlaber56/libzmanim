/****
Copyright (c) 2018 Y Paritcher

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser GeneralPublic License as published by the Free Software Foundation; 
either version 2.1 of the License, or (at your option)any later version.

This library is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; 
without even the impliedwarranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for more details. 
You should have received a copy of the GNU Lesser General Public License along with this library; 
if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA, 
or connect to: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
****/

#ifndef HEBREW_CALENDAR_H
#define HEBREW_CALENDAR_H

#include <time.h>

// location struct used to calculate zmanim
typedef struct {
	double latitude;
	double longitude;
	double elevation;
} location;

// enum of parshahs
typedef enum {NOPARSHAH, BERESHIT, NOACH, LECH_LECHA, VAYEIRA, CHAYEI_SARAH, TOLEDOT, VAYETZE, VAYISHLACH, VAYESHEV, MIKETZ, VAYIGASH, VAYECHI, SHEMOT, VAEIRA, BO, BESHALACH, YITRO, MISHPATIM, TERUMAH, TETZAVEH, KI_TISA, VAYAKHEL, PEKUDEI, VAYIKRA, TZAV, SHEMINI, TAZRIA, METZORA, ACHAREI_MOT, KEDOSHIM, EMOR, BEHAR, BECHUKOTAI, BAMIDBAR, NASO, BEHAALOTECHA, SHLACH, KORACH, CHUKAT, BALAK, PINCHAS, MATOT, MASEI, DEVARIM, VAETCHANAN, EIKEV, REEH, SHOFTIM, KI_TEITZEI, KI_TAVO, NITZAVIM, VAYELECH, HAAZINU, VZOT_HABERACHAH, VAYAKHEL_PEKUDEI, TAZRIA_METZORA, ACHAREI_MOT_KEDOSHIM, BEHAR_BECHUKOTAI, CHUKAT_BALAK, MATOT_MASEI, NITZAVIM_VAYELECH} parshah;

// enum of yomtovs
typedef enum {CHOL, PESACH_DAY1, PESACH_DAY2, SHVEI_SHEL_PESACH, ACHRON_SHEL_PESACH, SHAVOUS_DAY1, SHAVOUS_DAY2, ROSH_HASHANAH_DAY1, ROSH_HASHANAH_DAY2, YOM_KIPPUR, SUKKOS_DAY1, SUKKOS_DAY2, SHMEINI_ATZERES, SIMCHAS_TORAH, CHOL_HAMOED_PESACH_DAY1, CHOL_HAMOED_PESACH_DAY2, CHOL_HAMOED_PESACH_DAY3, CHOL_HAMOED_PESACH_DAY4, CHOL_HAMOED_PESACH_DAY5, CHOL_HAMOED_SUKKOS_DAY1, CHOL_HAMOED_SUKKOS_DAY2, CHOL_HAMOED_SUKKOS_DAY3, CHOL_HAMOED_SUKKOS_DAY4, CHOL_HAMOED_SUKKOS_DAY5, HOSHANA_RABBAH, PESACH_SHEINI, LAG_BAOMER, TU_BAV, CHANUKAH_DAY1, CHANUKAH_DAY2, CHANUKAH_DAY3, CHANUKAH_DAY4, CHANUKAH_DAY5, CHANUKAH_DAY6, CHANUKAH_DAY7, CHANUKAH_DAY8, TU_BISHVAT, PURIM_KATAN, SHUSHAN_PURIM_KATAN, PURIM, SHUSHAN_PURIM, SHIVA_ASAR_BTAAMUZ, TISHA_BAV, TZOM_GEDALIA, ASARAH_BTEVES, TAANIS_ESTER, EREV_PESACH, EREV_SHAVOUS, EREV_ROSH_HASHANAH, EREV_YOM_KIPPUR, EREV_SUKKOS, SHKALIM, ZACHOR, PARAH, HACHODESH, ROSH_CHODESH, MACHAR_CHODESH, SHABBOS_MEVORCHIM} yomtov;

//array of parshah year types
extern const parshah parshahlist[17][56];

// hdate struct
typedef struct {
	int year; // 0 - ∞
	int month; // starts from nissan 1 - 13
	int day; // 1 - 30
	int hour; // 0 - 23
	int min; // 0 - 59
	int sec; // 0 - 59
	int msec;
	int wday; // weekdays 1 - 6, 0
	int dayofyear; // starts from tishrei
	long int offset; // timezone offset in seconds
	_Bool leap; // if leap year
	_Bool EY; // if Eretz Yisroel (for yomtov & parshah)
} hdate;

// molad type: beware that the seconds are actually chalakim 1/1080 of an hour
// and that the hebrew date is actually the next one when the hour > 18
// also the molad is calculated in Yerushalayim Mean Time so cannot be easily converted.
typedef hdate molad;

// get length of given month
int LastDayOfHebrewMonth(int month, int year);

// is the year a leap year
int HebrewLeapYear(int year);

// day from molad tohu until Rosh Hashana
long int HebrewCalendarElapsedDays(int year);
// convert struct tm to hdate
hdate convertDate(struct tm date);
void setEY(hdate *date, _Bool EY);
// convert a hdate to julian day
double hdatejulian(hdate date);
// convert a hdate to gregorian date
struct tm hdategregorian(hdate date);
// convert a gregorian date to julian day
double gregorianjulian(struct tm date);
// convert a hdate to a time_t
time_t hdatetime_t(hdate date);

//compare 2 hdate:
// returns 0 if they are the same
// 1 if date1 < date2
// and -1 if date1 > date2
int hdatecompare(hdate date1, hdate date2);

// functions to add or subtract from a hdate field and then normalize the result
void hdateaddyear(hdate *date, int years);
void hdateaddmonth(hdate *date, int months);
void hdateaddday(hdate *date, int days);
void hdateaddhour(hdate *date, int hours);
void hdateaddminute(hdate *date, int minutes);
void hdateaddsecond(hdate *date, int seconds);
void hdateaddmsecond(hdate *date, int mseconds);
void hdateadd(hdate *date, int years, int months, int days, int hours, int minutes, int seconds, int mseconds);


// Returns the molad of the given month remember month 1 is Nissan
// beware that the seconds are actually chalakim 1/1080 of an hour
// and that the hebrew date is actually the next one when the hour > 18
// also the molad is calculated in Yerushalayim Mean Time so cannot be easily converted.
molad getmolad(int year, int month);

// if Shabbos get the current parshah otherwise return 0
parshah getparshah(hdate date);
// if yomtov get the current yomtov otherwise return 0
yomtov getyomtov(hdate date);
// if Shabbos get the current special parshah otherwise return 0
yomtov getspecialshabbos(hdate date);
// if rosh chodesh return rosh chodesh otherwise return 0
yomtov getroshchodesh(hdate date);
// if machar chodesh return machar chodesh otherwise return 0
yomtov getmacharchodesh(hdate date);
// if shabbos mevorchim return shabbos mevorchim otherwise return 0
yomtov getshabbosmevorchim(hdate date);
// The omer count 1 - 49 or 0 if none
int getomer(hdate date);
// if Shabbos get the current chapter of avos otherwise return 0
// returns 1 - 6 or 12 or 34 or 56 for double chapter
int getavos(hdate date);

_Bool istaanis(hdate date);
_Bool isassurbemelachah(hdate date);
// return 1 if cadlelighting regular, 2 if at nightfall, 3 if chanukah, or 0 if none
int iscandlelighting(hdate date);

// return true if birchas hachama on date
_Bool isbirchashachama(hdate date);

// return true if birchas hashanim is switched on date (winter)
_Bool isbirchashashanim(hdate date);
// return true if tal umatar livrachah is said in birchas hashanim
_Bool getbirchashashanim(hdate date);
#endif
