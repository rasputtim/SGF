/*
  SGF - Super Game Fabric  (https://sourceforge.net/projects/sgfabric/)
  Copyright (C) 2010-2011 Rasputtim <Rasputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */

#include "configuration/SGF_Configuration.h"
#include "SGF_Global.h"

//#pragma hdrstop

namespace SGF{


/*

All game cvars should be defined here.

*/
struct gameVersion_s {
    gameVersion_s() { std::sprintf( string, "%s.%d%s %s %s", ENGINE_VERSION, Global::BUILD_NUMBER, BUILD_DEBUG, BUILD_STRING, __DATE__, __TIME__ ); }
	char	string[256];
} gameVersion;

Token *	CSysVar::serialize(const CSysVar & cvar){
	SGF::Token * out = new SGF::Token();
    *out << "CSysVar";
	//*out->newToken() << "callback" << cvar.m_callback;
	//*out->newToken() << "calbackobject" << cvar.m_pObjectCallBack;
	*out->newToken() << "flags" << cvar.m_iFlags;
	*out->newToken() << "fvaluemin" << cvar.m_fValueMin;
	*out->newToken() << "fvaluemax" << cvar.m_fValueMax;
   *out->newToken() << "integervalue" << cvar.m_iIntegerValue;
   *out->newToken() << "floatvalue" << cvar.m_fFloatValue;
   *out->newToken() << "local" << cvar.m_bLocal;
   *out->newToken() << "name" << cvar.m_pName;
   *out->newToken() << "value" << cvar.m_pValue;
   *out->newToken() << "description" << cvar.m_pDescription;
   *out->newToken() << "onchangestatic" << cvar.m_executeStaticCalbackOnChange;
	*out->newToken() << "onchangeobject" << cvar.m_executeObjCalbackOnChange;

   if(m_ValueStrings) {
		Token * t1 = out->newToken();
		*t1 << "valuestrings";
		for ( int i = 0; m_ValueStrings[i] != NULL; i++ ) {
			*out->newToken() << "string"<<i << this->m_ValueStrings[i];
		}
   }
   if(m_pInternalVar) {
		Token * t2 = out->newToken();
		*t2 << "internalValue";
		*t2 << serialize(*m_pInternalVar);
   }
   //	argCompletion_t			m_tValueCompletion;		// value auto-completion function
	return out;
}
CSysVar::CSysVar( const CSysVar *cvar ){
	m_pName = cvar->m_pName ; 
	m_pValue = cvar->m_pValue;
	m_pDescription = cvar->m_pDescription;
	m_iFlags = cvar->m_iFlags;
	m_fValueMin = cvar->getMinValue();
	m_fValueMax = cvar->getMaxValue();
	// não copia aqui, copia na CEngineSyvar e CLocalCSysVar
	//m_ValueStrings = CopyValueStrings( cvar->getValueStrings() );
	m_tValueCompletion = cvar->getValueCompletion();
	m_pInternalVar = NULL;
	m_bLocal=cvar->m_bLocal;
	m_callback=cvar->m_callback;
	m_pObjectCallBack=cvar->m_pObjectCallBack;
    m_tValueCompletion=cvar->m_tValueCompletion;
	m_iIntegerValue=cvar->m_iIntegerValue;
	m_fFloatValue=cvar->m_fFloatValue;
	//CSysVar *				m_pNext;				// next statically declared cvar
	m_executeStaticCalbackOnChange=cvar->m_executeStaticCalbackOnChange;
	m_executeObjCalbackOnChange=cvar->m_executeObjCalbackOnChange;

}


CEngineSysVar g_version("g_version",gameVersion.string,	SYSVAR_GAME | SYSVAR_ROM, "game version" );
// noset vars
CEngineSysVar engineName("engineName",ENGINE_VERSION,	SYSVAR_GAME | SYSVAR_SERVERINFO | SYSVAR_ROM, "" );
CEngineSysVar engineDate("engineDate",__DATE__,		SYSVAR_GAME | SYSVAR_ROM, "" );
// server info
CEngineSysVar si_name("si_name","Game Server",	SYSVAR_GAME | SYSVAR_SERVERINFO | SYSVAR_ARCHIVE, "name of the server" );
//CEngineSysVar CConfiguration::si_gameType(					"si_gameType",		si_gameTypeArgs[ 0 ],	SYSVAR_GAME | SYSVAR_SERVERINFO | SYSVAR_ARCHIVE, "game type - singleplayer, deathmatch, Tourney, Team DM or Last Man", si_gameTypeArgs, idCmdSystem::ArgCompletion_String<si_gameTypeArgs> );
//CEngineSysVar CConfiguration::si_maxPlayers(				"si_maxPlayers",			"4",			SYSVAR_GAME | SYSVAR_SERVERINFO | SYSVAR_ARCHIVE | SYSVAR_INTEGER, "max number of players allowed on the server", 1, 4 );
//CEngineSysVar CConfiguration::si_timeLimit(				"si_timeLimit",				"10",			SYSVAR_GAME | SYSVAR_SERVERINFO | SYSVAR_ARCHIVE | SYSVAR_INTEGER, "time limit in minutes", 0, 60 );
CEngineSysVar si_teamDamage("si_teamDamage","0",			SYSVAR_GAME | SYSVAR_SERVERINFO | SYSVAR_ARCHIVE | SYSVAR_BOOL, "enable team damage" );
CEngineSysVar si_usePass("si_usePass","0",			SYSVAR_GAME | SYSVAR_SERVERINFO | SYSVAR_ARCHIVE | SYSVAR_BOOL, "enable client password checking" );
CEngineSysVar si_serverURL("si_serverURL","",				SYSVAR_GAME | SYSVAR_SERVERINFO | SYSVAR_ARCHIVE, "where to reach the server admins and get information about the server" );

// user info
CEngineSysVar ui_name("ui_name","Player",		SYSVAR_GAME | SYSVAR_USERINFO | SYSVAR_ARCHIVE, "player name" );
//CConfiguration::ui_team(						"ui_team",				ui_teamArgs[ 0 ],	SYSVAR_GAME | SYSVAR_USERINFO | SYSVAR_ARCHIVE, "player team", ui_teamArgs, idCmdSystem::ArgCompletion_String<ui_teamArgs> ); 
//CConfiguration::ui_ready(					"ui_ready",				si_readyArgs[ 0 ],	SYSVAR_GAME | SYSVAR_USERINFO, "player is ready to start playing", idCmdSystem::ArgCompletion_String<si_readyArgs> );
CEngineSysVar ui_chat("ui_chat","0",			SYSVAR_GAME | SYSVAR_USERINFO | SYSVAR_BOOL | SYSVAR_ROM | SYSVAR_CHEAT, "player is chatting" );
/*
// change anytime vars
CEngineSysVar CConfiguration::developer(					"developer",				"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );

CEngineSysVar CConfiguration::r_aspectRatio( 				"r_aspectRatio",			"0",			SYSVAR_RENDERER | SYSVAR_INTEGER | SYSVAR_ARCHIVE, "aspect ratio of view:\n0 = 4:3\n1 = 16:9\n2 = 16:10", 0, 2 );

CEngineSysVar CConfiguration::g_cinematic(					"g_cinematic",				"1",			SYSVAR_GAME | SYSVAR_BOOL, "skips updating entities that aren't marked 'cinematic' '1' during cinematics" );
CEngineSysVar CConfiguration::g_cinematicMaxSkipTime(		"g_cinematicMaxSkipTime",	"600",			SYSVAR_GAME | SYSVAR_FLOAT, "# of seconds to allow game to run when skipping cinematic.  prevents lock-up when cinematic doesn't end.", 0, 3600 );


CEngineSysVar CConfiguration::g_disasm(					"g_disasm",					"0",			SYSVAR_GAME | SYSVAR_BOOL, "disassemble script into base/script/disasm.txt on the local drive when script is compiled" );
CEngineSysVar CConfiguration::g_debugBounds(				"g_debugBounds",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "checks for models with bounds > 2048" );
CEngineSysVar CConfiguration::g_debugAnim(					"g_debugAnim",				"-1",			SYSVAR_GAME | SYSVAR_INTEGER, "displays information on which animations are playing on the specified entity number.  set to -1 to disable." );
CEngineSysVar CConfiguration::g_debugMove(					"g_debugMove",				"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_debugDamage(				"g_debugDamage",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_debugWeapon(				"g_debugWeapon",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_debugScript(				"g_debugScript",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_debugMover(				"g_debugMover",				"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_debugTriggers(				"g_debugTriggers",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_debugCinematic(			"g_debugCinematic",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_stopTime(					"g_stopTime",				"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_damageScale(				"g_damageScale",			"1",			SYSVAR_GAME | SYSVAR_FLOAT | SYSVAR_ARCHIVE, "scale final damage on player by this factor" );
CEngineSysVar CConfiguration::g_armorProtection(			"g_armorProtection",		"0.3",			SYSVAR_GAME | SYSVAR_FLOAT | SYSVAR_ARCHIVE, "armor takes this percentage of damage" );
CEngineSysVar CConfiguration::g_armorProtectionMP(			"g_armorProtectionMP",		"0.6",			SYSVAR_GAME | SYSVAR_FLOAT | SYSVAR_ARCHIVE, "armor takes this percentage of damage in mp" );
CEngineSysVar CConfiguration::g_useDynamicProtection(		"g_useDynamicProtection",	"1",			SYSVAR_GAME | SYSVAR_BOOL | SYSVAR_ARCHIVE, "scale damage and armor dynamically to keep the player alive more often" );
CEngineSysVar CConfiguration::g_healthTakeTime(			"g_healthTakeTime",			"5",			SYSVAR_GAME | SYSVAR_INTEGER | SYSVAR_ARCHIVE, "how often to take health in nightmare mode" );
CEngineSysVar CConfiguration::g_healthTakeAmt(				"g_healthTakeAmt",			"5",			SYSVAR_GAME | SYSVAR_INTEGER | SYSVAR_ARCHIVE, "how much health to take in nightmare mode" );
CEngineSysVar CConfiguration::g_healthTakeLimit(			"g_healthTakeLimit",		"25",			SYSVAR_GAME | SYSVAR_INTEGER | SYSVAR_ARCHIVE, "how low can health get taken in nightmare mode" );



CEngineSysVar CConfiguration::g_showPVS(					"g_showPVS",				"0",			SYSVAR_GAME | SYSVAR_INTEGER, "", 0, 2 );
CEngineSysVar CConfiguration::g_showCollisionWorld(		"g_showCollisionWorld",		"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_showCollisionModels(		"g_showCollisionModels",	"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_showCollisionTraces(		"g_showCollisionTraces",	"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_maxShowDistance(			"g_maxShowDistance",		"128",			SYSVAR_GAME | SYSVAR_FLOAT, "" );
CEngineSysVar CConfiguration::g_showEntityInfo(			"g_showEntityInfo",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_showviewpos(				"g_showviewpos",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_showcamerainfo(			"g_showcamerainfo",			"0",			SYSVAR_GAME | SYSVAR_ARCHIVE, "displays the current frame # for the camera when playing cinematics" );
CEngineSysVar CConfiguration::g_showTestModelFrame(		"g_showTestModelFrame",		"0",			SYSVAR_GAME | SYSVAR_BOOL, "displays the current animation and frame # for testmodels" );
CEngineSysVar CConfiguration::g_showActiveEntities(		"g_showActiveEntities",		"0",			SYSVAR_GAME | SYSVAR_BOOL, "draws boxes around thinking entities.  dormant entities (outside of pvs) are drawn yellow.  non-dormant are green." );
CEngineSysVar CConfiguration::g_showEnemies(				"g_showEnemies",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "draws boxes around monsters that have targeted the the player" );

CEngineSysVar CConfiguration::g_frametime(					"g_frametime",				"0",			SYSVAR_GAME | SYSVAR_BOOL, "displays timing information for each game frame" );
CEngineSysVar CConfiguration::g_timeentities(				"g_timeEntities",			"0",			SYSVAR_GAME | SYSVAR_FLOAT, "when non-zero, shows entities whose think functions exceeded the # of milliseconds specified" );
	
CEngineSysVar CConfiguration::ai_debugScript(				"ai_debugScript",			"-1",			SYSVAR_GAME | SYSVAR_INTEGER, "displays script calls for the specified monster entity number" );
CEngineSysVar CConfiguration::ai_debugMove(				"ai_debugMove",				"0",			SYSVAR_GAME | SYSVAR_BOOL, "draws movement information for monsters" );
CEngineSysVar CConfiguration::ai_debugTrajectory(			"ai_debugTrajectory",		"0",			SYSVAR_GAME | SYSVAR_BOOL, "draws trajectory tests for monsters" );
CEngineSysVar CConfiguration::ai_testPredictPath(			"ai_testPredictPath",		"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::ai_showCombatNodes(			"ai_showCombatNodes",		"0",			SYSVAR_GAME | SYSVAR_BOOL, "draws attack cones for monsters" );
CEngineSysVar CConfiguration::ai_showPaths(				"ai_showPaths",				"0",			SYSVAR_GAME | SYSVAR_BOOL, "draws path_* entities" );
CEngineSysVar CConfiguration::ai_showObstacleAvoidance(	"ai_showObstacleAvoidance",	"0",			SYSVAR_GAME | SYSVAR_INTEGER, "draws obstacle avoidance information for monsters.  if 2, draws obstacles for player, as well", 0, 2, idCmdSystem::ArgCompletion_Integer<0,2> );
CEngineSysVar CConfiguration::ai_blockedFailSafe(			"ai_blockedFailSafe",		"1",			SYSVAR_GAME | SYSVAR_BOOL, "enable blocked fail safe handling" );
	
CEngineSysVar CConfiguration::g_dvTime(					"g_dvTime",					"1",			SYSVAR_GAME | SYSVAR_FLOAT, "" );
CEngineSysVar CConfiguration::g_dvAmplitude(				"g_dvAmplitude",			"0.001",		SYSVAR_GAME | SYSVAR_FLOAT, "" );
CEngineSysVar CConfiguration::g_dvFrequency(				"g_dvFrequency",			"0.5",			SYSVAR_GAME | SYSVAR_FLOAT, "" );

CEngineSysVar CConfiguration::g_kickTime(					"g_kickTime",				"1",			SYSVAR_GAME | SYSVAR_FLOAT, "" );
CEngineSysVar CConfiguration::g_kickAmplitude(				"g_kickAmplitude",			"0.0001",		SYSVAR_GAME | SYSVAR_FLOAT, "" );
CEngineSysVar CConfiguration::g_blobTime(					"g_blobTime",				"1",			SYSVAR_GAME | SYSVAR_FLOAT, "" );
CEngineSysVar CConfiguration::g_blobSize(					"g_blobSize",				"1",			SYSVAR_GAME | SYSVAR_FLOAT, "" );

CEngineSysVar CConfiguration::g_testHealthVision(			"g_testHealthVision",		"0",			SYSVAR_GAME | SYSVAR_FLOAT, "" );
CEngineSysVar CConfiguration::g_editEntityMode(			"g_editEntityMode",			"0",			SYSVAR_GAME | SYSVAR_INTEGER,	"0 = off\n"
																											"1 = lights\n"
																											"2 = sounds\n"
																											"3 = articulated figures\n"
																											"4 = particle systems\n"
																											"5 = monsters\n"
																											"6 = entity names\n"
																											"7 = entity models", 0, 7, idCmdSystem::ArgCompletion_Integer<0,7> );
CEngineSysVar CConfiguration::g_dragEntity(				"g_dragEntity",				"0",			SYSVAR_GAME | SYSVAR_BOOL, "allows dragging physics objects around by placing the crosshair over them and holding the fire button" );
CEngineSysVar CConfiguration::g_dragDamping(				"g_dragDamping",			"0.5",			SYSVAR_GAME | SYSVAR_FLOAT, "" );
CEngineSysVar CConfiguration::g_dragShowSelection(			"g_dragShowSelection",		"0",			SYSVAR_GAME | SYSVAR_BOOL, "" );
CEngineSysVar CConfiguration::g_dropItemRotation(			"g_dropItemRotation",		"",				SYSVAR_GAME, "" );


CEngineSysVar CConfiguration::ik_enable(					"ik_enable",				"1",			SYSVAR_GAME | SYSVAR_BOOL, "enable IK" );
CEngineSysVar CConfiguration::ik_debug(					"ik_debug",					"0",			SYSVAR_GAME | SYSVAR_BOOL, "show IK debug lines" );

CEngineSysVar CConfiguration::af_useLinearTime(			"af_useLinearTime",			"1",			SYSVAR_GAME | SYSVAR_BOOL, "use linear time algorithm for tree-like structures" );
CEngineSysVar CConfiguration::af_useImpulseFriction(		"af_useImpulseFriction",	"0",			SYSVAR_GAME | SYSVAR_BOOL, "use impulse based contact friction" );
CEngineSysVar CConfiguration::af_useJointImpulseFriction(	"af_useJointImpulseFriction","0",			SYSVAR_GAME | SYSVAR_BOOL, "use impulse based joint friction" );
CEngineSysVar CConfiguration::af_useSymmetry(				"af_useSymmetry",			"1",			SYSVAR_GAME | SYSVAR_BOOL, "use constraint matrix symmetry" );
CEngineSysVar CConfiguration::af_skipSelfCollision(		"af_skipSelfCollision",		"0",			SYSVAR_GAME | SYSVAR_BOOL, "skip self collision detection" );
CEngineSysVar CConfiguration::af_skipLimits(				"af_skipLimits",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "skip joint limits" );
CEngineSysVar CConfiguration::af_skipFriction(				"af_skipFriction",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "skip friction" );
CEngineSysVar CConfiguration::af_forceFriction(			"af_forceFriction",			"-1",			SYSVAR_GAME | SYSVAR_FLOAT, "force the given friction value" );
CEngineSysVar CConfiguration::af_maxLinearVelocity(		"af_maxLinearVelocity",		"128",			SYSVAR_GAME | SYSVAR_FLOAT, "maximum linear velocity" );
CEngineSysVar CConfiguration::af_maxAngularVelocity(		"af_maxAngularVelocity",	"1.57",			SYSVAR_GAME | SYSVAR_FLOAT, "maximum angular velocity" );
CEngineSysVar CConfiguration::af_timeScale(				"af_timeScale",				"1",			SYSVAR_GAME | SYSVAR_FLOAT, "scales the time" );
CEngineSysVar CConfiguration::af_jointFrictionScale(		"af_jointFrictionScale",	"0",			SYSVAR_GAME | SYSVAR_FLOAT, "scales the joint friction" );
CEngineSysVar CConfiguration::af_contactFrictionScale(		"af_contactFrictionScale",	"0",			SYSVAR_GAME | SYSVAR_FLOAT, "scales the contact friction" );
CEngineSysVar CConfiguration::af_highlightBody(			"af_highlightBody",			"",				SYSVAR_GAME, "name of the body to highlight" );
CEngineSysVar CConfiguration::af_highlightConstraint(		"af_highlightConstraint",	"",				SYSVAR_GAME, "name of the constraint to highlight" );
CEngineSysVar CConfiguration::af_showTimings(				"af_showTimings",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "show articulated figure cpu usage" );
CEngineSysVar CConfiguration::af_showConstraints(			"af_showConstraints",		"0",			SYSVAR_GAME | SYSVAR_BOOL, "show constraints" );
CEngineSysVar CConfiguration::af_showConstraintNames(		"af_showConstraintNames",	"0",			SYSVAR_GAME | SYSVAR_BOOL, "show constraint names" );
CEngineSysVar CConfiguration::af_showConstrainedBodies(	"af_showConstrainedBodies",	"0",			SYSVAR_GAME | SYSVAR_BOOL, "show the two bodies contrained by the highlighted constraint" );
CEngineSysVar CConfiguration::af_showPrimaryOnly(			"af_showPrimaryOnly",		"0",			SYSVAR_GAME | SYSVAR_BOOL, "show primary constraints only" );
CEngineSysVar CConfiguration::af_showTrees(				"af_showTrees",				"0",			SYSVAR_GAME | SYSVAR_BOOL, "show tree-like structures" );
CEngineSysVar CConfiguration::af_showLimits(				"af_showLimits",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "show joint limits" );
CEngineSysVar CConfiguration::af_showBodies(				"af_showBodies",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "show bodies" );
CEngineSysVar CConfiguration::af_showBodyNames(			"af_showBodyNames",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "show body names" );
CEngineSysVar CConfiguration::af_showMass(					"af_showMass",				"0",			SYSVAR_GAME | SYSVAR_BOOL, "show the mass of each body" );
CEngineSysVar CConfiguration::af_showTotalMass(			"af_showTotalMass",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "show the total mass of each articulated figure" );
CEngineSysVar CConfiguration::af_showInertia(				"af_showInertia",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "show the inertia tensor of each body" );
CEngineSysVar CConfiguration::af_showVelocity(				"af_showVelocity",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "show the velocity of each body" );
CEngineSysVar CConfiguration::af_showActive(				"af_showActive",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "show tree-like structures of articulated figures not at rest" );
CEngineSysVar CConfiguration::af_testSolid(				"af_testSolid",				"1",			SYSVAR_GAME | SYSVAR_BOOL, "test for bodies initially stuck in solid" );

CEngineSysVar CConfiguration::rb_showTimings(				"rb_showTimings",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "show rigid body cpu usage" );
CEngineSysVar CConfiguration::rb_showBodies(				"rb_showBodies",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "show rigid bodies" );
CEngineSysVar CConfiguration::rb_showMass(					"rb_showMass",				"0",			SYSVAR_GAME | SYSVAR_BOOL, "show the mass of each rigid body" );
CEngineSysVar CConfiguration::rb_showInertia(				"rb_showInertia",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "show the inertia tensor of each rigid body" );
CEngineSysVar CConfiguration::rb_showVelocity(				"rb_showVelocity",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "show the velocity of each rigid body" );
CEngineSysVar CConfiguration::rb_showActive(				"rb_showActive",			"0",			SYSVAR_GAME | SYSVAR_BOOL, "show rigid bodies that are not at rest" );

																							"0 = cycle anim with origin reset\n"
																							"1 = cycle anim with fixed origin\n"
																							"2 = cycle anim with continuous origin\n"
																							"3 = frame by frame with continuous origin\n"
																							"4 = play anim once", 0, 4, idCmdSystem::ArgCompletion_Integer<0,4> );
*/
}
