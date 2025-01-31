#pragma once


/*!
 *  @brief      eí
 */
enum class BULLET_TYPE
{
    NORMAL,     // Êíe
    REFLECT,    // ½Ëe
    PENETRATE,  // n`ÑÊe
    BEAM,       // Qt...r[
    MAX
};


/*!
 *  @brief      eîñ
 */
struct BULLET_INFO
{
    BULLET_TYPE bullet_type = BULLET_TYPE::NORMAL;  // eí
    int     damage = 1;                             // _[Wl
    float   radius = 5.0f;                          // ĵa
    float   speed = 1.0f;                           // eĴ
    std::string bullet_name;                        // eíĵ
};
