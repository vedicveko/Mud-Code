/*****************************************************************************
**                                                                          **
** Skills for mobiles.                                                      **
**                                                                          **
**                                                       Vedic -- 10/20/99  **
**                                                                          **
*****************************************************************************/

#include "conf.h"
#include "sysdep.h"


#include "structs.h"
#include "utils.h"
#include "comm.h"
#include "interpreter.h"
#include "handler.h"
#include "db.h"
#include "spells.h"


void do_mob_bash(struct char_data *ch, struct char_data *vict)
{

  int hit_roll = 0, to_hit = 0;
  
  hit_roll = number (1,100) + GET_STR(ch);
  to_hit = (100 - (int) (100*GET_LEVEL(ch)/250));
  if (GET_LEVEL(vict) >= LVL_IMMORT)  
    hit_roll = 0;

  if (hit_roll < to_hit) {
    GET_POS(ch) = POS_SITTING;
    damage(ch, vict, 0, SKILL_BASH, ABT_SKILL);
  } else {
    GET_POS(vict) = POS_SITTING;
    damage(ch, vict, GET_LEVEL(ch), SKILL_BASH, ABT_SKILL);
    WAIT_STATE(vict, PULSE_VIOLENCE * 2);
    WAIT_STATE(ch, PULSE_VIOLENCE * 3);
  }

}

void do_mob_disarm(struct char_data *ch, struct char_data *vict)
{

  int hit_roll = 0, to_hit = 0;
  struct obj_data *weap; 
 
  hit_roll = number (1,100) + GET_DEX(ch);
  to_hit = (100 - (int) (100*GET_LEVEL(ch)/250));
  if (GET_LEVEL(vict) >= LVL_IMMORT)  
    hit_roll = 0;

  if (!(weap = GET_EQ(FIGHTING(ch), WEAR_WIELD))) {
    send_to_char("Nope, sorry\r\n", ch);
    return;      
  }

  if (hit_roll < to_hit) { 	/* Disarm */
    act("You knock $p from $N's hand!", FALSE, ch, weap, FIGHTING(ch), TO_CHAR);
    act("$n knocks $p from your hand!", FALSE, ch, weap, FIGHTING(ch), TO_VICT); 
    act("$n knocks $p from $N's hand!", FALSE, ch, weap, FIGHTING(ch), TO_ROOM);
    obj_to_char(unequip_char(FIGHTING(ch), WEAR_WIELD), FIGHTING(ch));
  } else {
    act("You fail to disarm $N", FALSE, ch, weap, FIGHTING(ch), TO_CHAR);
    act("$n fails to disarm you", FALSE, ch, weap, FIGHTING(ch), TO_VICT);
    act("$n fails to disarm $N", FALSE, ch, weap, FIGHTING(ch), TO_ROOM);
  }
  WAIT_STATE(ch, PULSE_VIOLENCE);

}

void do_mob_kickflip(struct char_data *ch, struct char_data *vict)
{

  int hit_roll = 0, to_hit = 0;
  
  hit_roll = number (1,100) + GET_STR(ch);
  to_hit = (100 - (int) (100*GET_LEVEL(ch)/250));
  if (GET_LEVEL(vict) >= LVL_IMMORT)  
    hit_roll = 0;

  if (hit_roll < to_hit) {
    GET_POS(ch) = POS_SITTING;
    damage(ch, vict, 0, SKILL_KICKFLIP, ABT_SKILL);
  } else {
    GET_POS(vict) = POS_SITTING;
    damage(ch, vict, GET_LEVEL(ch), SKILL_KICKFLIP, ABT_SKILL);
    WAIT_STATE(vict, PULSE_VIOLENCE * 2);
    WAIT_STATE(ch, PULSE_VIOLENCE * 3);
  }

}


/* This is for straight damage skills like kick and such. */

void do_generic_skill(struct char_data *ch, struct char_data *vict, int type)
{

  int hit_roll = 0, to_hit = 0;
  
  hit_roll = number (1,100) + GET_STR(ch);
  to_hit = (100 - (int) (100*GET_LEVEL(ch)/250));
  if (GET_LEVEL(vict) >= LVL_IMMORT)  
    hit_roll = 0;

  if (hit_roll < to_hit) {       
    damage(ch, vict, 0, type, ABT_SKILL);
  } else {
    damage(ch, vict, GET_LEVEL(ch), type, ABT_SKILL);
  }  
  WAIT_STATE(ch, PULSE_VIOLENCE * 2);
}
