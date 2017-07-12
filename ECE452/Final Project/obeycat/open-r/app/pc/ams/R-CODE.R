:1000	// Main:START
GO:1005
:1001	// Main:MainLoop
:1002	// Main:BatteryLow?
WAIT:1
IF_1ST:Batt_Rest:<:20:1003
GO:1012
:1003	// Main:PowerDown
PLAY:ACTION:CHGPOS.STATR.NORMAL
WAIT
PLAY:ACTION+:thats_all_folks
WAIT
HALT
:1004	// Main:powerdown
EXIT
:1005	// Main:FellDown_or_GotOff?
WAIT:1
IF_1ST:Status:=:1:1007
GO:1006
:1006	// Main:WakeupSong
PLAY:ACTION:SIT
WAIT
PLAY:ACTION+:roar
WAIT
GO:1008
:1007	// Main:BadBack
PLAY:ACTION:SIT
WAIT
PLAY:ACTION+:badback
WAIT
:1008	// Main:RCodePlus?
WAIT:1
IF_1ST:AP_Version:>=:250:1016
GO:1010
:1009	// Main:done1
EXIT
:1010	// Main:Bad_Install
PLAY:ACTION:SMESS.ERROR.ERROR1
WAIT
PLAY:ACTION+:thats_all_folks
WAIT
QUIT
GO:1009
:1011	// Main:SetMode
VLOAD:AP_Vocab
SET:isWalking:0
SET:idle_count:0
CLR:SENSORS
GO:1015
:1012	// Main:IsWalking?
WAIT:1
IF_1ST:isWalking:>:0:1013
GO:1014
:1013	// Main:Main_Walking
CALL:1204
CASE:1:GO:1001
EXIT
:1014	// Main:Main_Not_Walking
CALL:1181
CASE:1:GO:1001
EXIT
:1015	// Main:Vocab_ok?
WAIT:1
IF_1ST:AP_Vocab:=:2:1001
GO:1010
:1016	// Main:INCLUDE_CUSTOM_RCR(1)
CALL:1264
CASE:1:GO:1011
EXIT
EXIT
:1017	// Pick_1_of_6:ENTRY
GO:1022
:1018	// Pick_1_of_6:Pick_1_of_6
WAIT:1
IF_1ST:randval:=:1:1019
IF_1ST:randval:=:2:1020
IF_1ST:randval:=:3:1021
IF_1ST:randval:=:4:1023
IF_1ST:randval:=:5:1024
GO:1025
:1019	// Pick_1_of_6:rand1
RET:1
:1020	// Pick_1_of_6:rand2
RET:2
:1021	// Pick_1_of_6:rand3
RET:3
:1022	// Pick_1_of_6:Rand6
RND:randval:1:6
GO:1018
:1023	// Pick_1_of_6:rand4
RET:4
:1024	// Pick_1_of_6:rand5
RET:5
:1025	// Pick_1_of_6:rand6
RET:6
EXIT
EXIT
:1033	// Handle_BackMode:ENTRY
GO:1035
:1034	// Handle_BackMode:RETURN
RET:1
:1035	// Handle_BackMode:AskAiboPaws
CALL:1042
CASE:1:GO:1039
CASE:2:GO:1040
CASE:3:GO:1041
CASE:4:GO:1036
CASE:5:GO:1037
CASE:6:GO:1038
EXIT
:1036	// Handle_BackMode:DANCE4
PLAY:ACTION+:DANCE4
WAIT
GO:1034
:1037	// Handle_BackMode:DANCE5
PLAY:ACTION+:DANCE5
WAIT
GO:1034
:1038	// Handle_BackMode:DANCE6
PLAY:ACTION+:DANCE6
WAIT
GO:1034
:1039	// Handle_BackMode:DANCE1
PLAY:ACTION+:DANCE1
WAIT
GO:1034
:1040	// Handle_BackMode:DANCE2
PLAY:ACTION+:DANCE2
WAIT
GO:1034
:1041	// Handle_BackMode:DANCE3
PLAY:ACTION+:DANCE3
WAIT
GO:1034
EXIT
:1042	// AskAiboPaws:ENTRY
GO:1047
:1043	// AskAiboPaws:eye1
SET:LFLeg_ON:0
SET:RFLeg_ON:0
SET:Head_ON:0
PLAY:ACTION+:eye_sel01
:1044	// AskAiboPaws:test1
WAIT:1
IF_1ST:RFLeg_ON:>:0:1054
IF_1ST:Head_ON:>:0:1062
IF_1ST:LFLeg_ON:>:0:1045
GO:1044
:1045	// AskAiboPaws:eye2
SET:LFLeg_ON:0
SET:RFLeg_ON:0
SET:Head_ON:0
PLAY:ACTION+:eye_sel02
:1046	// AskAiboPaws:test2
WAIT:1
IF_1ST:RFLeg_ON:>:0:1043
IF_1ST:Head_ON:>:0:1063
IF_1ST:LFLeg_ON:>:0:1048
GO:1046
:1047	// AskAiboPaws:AskPosition
PLAY:ACTION:LIE
WAIT
PLAY:ACTION+:AskPosition
WAIT
GO:1043
:1048	// AskAiboPaws:eye3_[8]
SET:LFLeg_ON:0
SET:RFLeg_ON:0
SET:Head_ON:0
PLAY:ACTION+:eye_sel08
:1049	// AskAiboPaws:test3
WAIT:1
IF_1ST:RFLeg_ON:>:0:1045
IF_1ST:Head_ON:>:0:1064
IF_1ST:LFLeg_ON:>:0:1050
GO:1049
:1050	// AskAiboPaws:eye4_[32]
SET:LFLeg_ON:0
SET:RFLeg_ON:0
SET:Head_ON:0
PLAY:ACTION+:eye_sel32
:1051	// AskAiboPaws:test4
WAIT:1
IF_1ST:RFLeg_ON:>:0:1048
IF_1ST:Head_ON:>:0:1065
IF_1ST:LFLeg_ON:>:0:1052
GO:1051
:1052	// AskAiboPaws:eye5_[16]
SET:LFLeg_ON:0
SET:RFLeg_ON:0
SET:Head_ON:0
PLAY:ACTION+:eye_sel16
:1053	// AskAiboPaws:test5
WAIT:1
IF_1ST:RFLeg_ON:>:0:1050
IF_1ST:Head_ON:>:0:1066
IF_1ST:LFLeg_ON:>:0:1054
GO:1053
:1054	// AskAiboPaws:eye6_[4]
SET:LFLeg_ON:0
SET:RFLeg_ON:0
SET:Head_ON:0
PLAY:ACTION+:eye_sel04
:1055	// AskAiboPaws:test6
WAIT:1
IF_1ST:RFLeg_ON:>:0:1052
IF_1ST:Head_ON:>:0:1067
IF_1ST:LFLeg_ON:>:0:1043
GO:1055
:1056	// AskAiboPaws:1
RET:1
:1057	// AskAiboPaws:2
RET:2
:1058	// AskAiboPaws:3
RET:3
:1059	// AskAiboPaws:4
RET:4
:1060	// AskAiboPaws:5
RET:5
:1061	// AskAiboPaws:6
RET:6
:1062	// AskAiboPaws:ClearEyes
PLAY:ACTION+:eye_clear
WAIT
GO:1056
:1063	// AskAiboPaws:ClearEyes(2)
PLAY:ACTION+:eye_clear
WAIT
GO:1057
:1064	// AskAiboPaws:ClearEyes(3)
PLAY:ACTION+:eye_clear
WAIT
GO:1058
:1065	// AskAiboPaws:ClearEyes(4)
PLAY:ACTION+:eye_clear
WAIT
GO:1059
:1066	// AskAiboPaws:ClearEyes(5)
PLAY:ACTION+:eye_clear
WAIT
GO:1060
:1067	// AskAiboPaws:ClearEyes(6)
PLAY:ACTION+:eye_clear
WAIT
GO:1061
EXIT
:1068	// CheckVoice:ENTRY
GO:1071
:1069	// CheckVoice:got_voice
RET:1
:1070	// CheckVoice:StartVoiceCmd
SET:theVoiceCmd:AP_Voice_Cmd
SET:theVoiceLevel:AP_Voice_Level
SET:theVoicePitch:AP_Voice_Pitch
SET:theVoiceHorz:AP_Voice_Horz
SET:AP_Voice_Cmd:0
GO:1069
:1071	// CheckVoice:VoiceCmd?
WAIT:1
IF_1ST:AP_Voice_Cmd:<>:0:1070
GO:1072
:1072	// CheckVoice:no_voice
RET:2
EXIT
:1073	// Handle_VoiceCommands:ENTRY
GO:1085
:1074	// Handle_VoiceCommands:done
RET:1
:1075	// Handle_VoiceCommands:Stand
PLAY:ACTION:STAND
WAIT
GO:1074
:1076	// Handle_VoiceCommands:Sit
PLAY:ACTION:SIT
WAIT
GO:1074
:1077	// Handle_VoiceCommands:Lie
PLAY:ACTION:LIE
WAIT
GO:1074
:1078	// Handle_VoiceCommands:Fwd
PLAY:ACTION:WALK:0:10000
SET:isWalking:1
GO:1074
:1079	// Handle_VoiceCommands:Rev
PLAY:ACTION:WALK:180:10000
SET:isWalking:1
GO:1074
:1080	// Handle_VoiceCommands:Stop
PLAY:ACTION:STOP_WALK
WAIT
GO:1074
:1081	// Handle_VoiceCommands:Good_Boy?
WAIT:1
IF_1ST:theVoiceCmd:=:61:1102
IF_1ST:theVoiceCmd:=:62:1102
GO:1103
:1082	// Handle_VoiceCommands:Take_Picture?
WAIT:1
IF_1ST:theVoiceCmd:=:55:1105
GO:1081
:1083	// Handle_VoiceCommands:Dance?
WAIT:1
IF_1ST:theVoiceCmd:=:21:1096
GO:1098
:1084	// Handle_VoiceCommands:Whats_your_name?
WAIT:1
IF_1ST:theVoiceCmd:=:2:1111
GO:1107
:1085	// Handle_VoiceCommands:Std_Sit_Lie?
WAIT:1
IF_1ST:theVoiceCmd:=:30:1075
IF_1ST:theVoiceCmd:=:32:1076
IF_1ST:theVoiceCmd:=:31:1077
GO:1086
:1086	// Handle_VoiceCommands:Fwd_Rev_Stop?
WAIT:1
IF_1ST:theVoiceCmd:=:35:1078
IF_1ST:theVoiceCmd:=:36:1079
IF_1ST:theVoiceCmd:=:38:1080
GO:1087
:1087	// Handle_VoiceCommands:TurnL_R?
WAIT:1
IF_1ST:theVoiceCmd:=:34:1088
IF_1ST:theVoiceCmd:=:33:1089
GO:1100
:1088	// Handle_VoiceCommands:TurnL
PLAY:ACTION:MOVE.TURN.NORMAL:10000
SET:isWalking:1
GO:1074
:1089	// Handle_VoiceCommands:TurnR
PLAY:ACTION:MOVE.TURN.NORMAL:-10000
SET:isWalking:1
GO:1074
:1090	// Handle_VoiceCommands:ComeHere?
WAIT:1
IF_1ST:theVoiceCmd:=:54:1094
GO:1091
:1091	// Handle_VoiceCommands:KickBall?
WAIT:1
IF_1ST:theVoiceCmd:=:42:1092
IF_1ST:theVoiceCmd:=:44:1117
GO:1082
:1092	// Handle_VoiceCommands:KickR
PLAY:ACTION:KICK:-30:1000
WAIT
GO:1074
:1093	// Handle_VoiceCommands:Wassup?
PLAY:ACTION+:whats_up
WAIT
GO:1074
:1094	// Handle_VoiceCommands:TurnInDirectionOfVoice
CALL:1118
CASE:1:GO:1095
EXIT
:1095	// Handle_VoiceCommands:StartWalking
PLAY:ACTION:WALK:0:10000
SET:isWalking:1
GO:1074
:1096	// Handle_VoiceCommands:Dance
CALL:1157
CASE:1:GO:1074
EXIT
:1097	// Handle_VoiceCommands:start_purr
PLAY:ACTION+:purr
SET:isPurring:1
GO:1074
:1098	// Handle_VoiceCommands:(spacer1)
GO:1090
:1099	// Handle_VoiceCommands:ToStation
PLAY:ACTION:CHGPOS.STATR.NORMAL
WAIT
GO:1074
:1100	// Handle_VoiceCommands:GoodNight?
WAIT:1
IF_1ST:theVoiceCmd:=:7:1099
GO:1083
:1101	// Handle_VoiceCommands:(spacer2)
GO:1106
:1102	// Handle_VoiceCommands:isPurring?
WAIT:1
IF_1ST:isPurring:<>:0:1074
GO:1097
:1103	// Handle_VoiceCommands:LetsPlay_Talk?
WAIT:1
IF_1ST:theVoiceCmd:=:19:1116
IF_1ST:theVoiceCmd:=:65:1116
GO:1101
:1104	// Handle_VoiceCommands:Whats_owners_name?
WAIT:1
IF_1ST:theVoiceCmd:=:67:1113
GO:1115
:1105	// Handle_VoiceCommands:TakeAPicture
CALL:RCR_TakeAPicture
GO:1074
:1106	// Handle_VoiceCommands:Name_Reg?
WAIT:1
IF_1ST:theVoiceCmd:=:60:1110
GO:1084
:1107	// Handle_VoiceCommands:Owner_Reg?
WAIT:1
IF_1ST:theVoiceCmd:=:68:1112
GO:1104
:1108	// Handle_VoiceCommands:(spacer3)
GO:1074
:1109	// Handle_VoiceCommands:Hear_OwnerName?
WAIT:1
IF_1ST:theVoiceCmd:=:256:1093
GO:1108
:1110	// Handle_VoiceCommands:RecordDogsName
CALL:RCR_RecordDogsName
GO:1074
:1111	// Handle_VoiceCommands:SayDogsName
CALL:RCR_SayDogsName
GO:1074
:1112	// Handle_VoiceCommands:RecordOwnersName
CALL:RCR_RecordOwnersName
GO:1074
:1113	// Handle_VoiceCommands:SayOwnersName
CALL:RCR_SayOwnersName
GO:1074
:1114	// Handle_VoiceCommands:Roar
PLAY:ACTION+:roar
WAIT
GO:1074
:1115	// Handle_VoiceCommands:Hear_Name
WAIT:1
IF_1ST:theVoiceCmd:=:1:1114
GO:1109
:1116	// Handle_VoiceCommands:CheesyMimicMode
PLAY:ACTION:SIT
WAIT
CALL:RCR_CheesyMimicMode
PLAY:ACTION+:thats_all_folks
WAIT
GO:1074
:1117	// Handle_VoiceCommands:KickL
PLAY:ACTION:KICK:30:1000
WAIT
GO:1074
EXIT
:1118	// TurnInDirectionOfVoice:ENTRY
GO:1126
:1119	// TurnInDirectionOfVoice:RETURN
RET:1
:1120	// TurnInDirectionOfVoice:B
PLAY:ACTION+:wink03
PLAY:ACTION:TURN:180
WAIT
GO:1119
:1121	// TurnInDirectionOfVoice:FR
PLAY:ACTION+:wink16
PLAY:ACTION:MOVE.HEAD.FAST:-50:20
PLAY:ACTION:TURN:-100
WAIT
PLAY:ACTION:MOVE.HEAD.FAST:0:0
GO:1119
:1122	// TurnInDirectionOfVoice:R
PLAY:ACTION+:wink04
PLAY:ACTION:TURN:-120
WAIT
GO:1119
:1123	// TurnInDirectionOfVoice:BL
PLAY:ACTION+:wink02
PLAY:ACTION:TURN:160
WAIT
GO:1119
:1124	// TurnInDirectionOfVoice:L
PLAY:ACTION+:wink08
PLAY:ACTION:TURN:120
WAIT
GO:1119
:1125	// TurnInDirectionOfVoice:FL
PLAY:ACTION+:wink32
PLAY:ACTION:MOVE.HEAD.FAST:50:20
PLAY:ACTION:TURN:60
WAIT
PLAY:ACTION:MOVE.HEAD.FAST:0:0
GO:1119
:1126	// TurnInDirectionOfVoice:Check_Horz
WAIT:1
IF_1ST:theVoiceHorz:&:1:1128
IF_1ST:theVoiceHorz:&:2:1121
IF_1ST:theVoiceHorz:&:4:1122
IF_1ST:theVoiceHorz:&:8:1127
IF_1ST:theVoiceHorz:&:16:1120
IF_1ST:theVoiceHorz:&:32:1123
IF_1ST:theVoiceHorz:&:64:1124
IF_1ST:theVoiceHorz:&:128:1125
GO:1119
:1127	// TurnInDirectionOfVoice:BR
PLAY:ACTION+:wink01
PLAY:ACTION:TURN:-160
WAIT
GO:1119
:1128	// TurnInDirectionOfVoice:F
PLAY:ACTION+:wink48
PLAY:ACTION:MOVE.HEAD.FAST:0:20
GO:1119
EXIT
:1129	// CheckAiboSound:ENTRY
GO:1132
:1130	// CheckAiboSound:got_tone
RET:1
:1131	// CheckAiboSound:StartAiboSound
SET:theAiboSound:AU_AiboSound_ID
SET:AU_AiboSound
GO:1130
:1132	// CheckAiboSound:AiboSound?
WAIT:1
IF_1ST:AU_AiboSound:<>:0:1131
GO:1133
:1133	// CheckAiboSound:no_tone
RET:2
EXIT
:1134	// CheckSoundControllerTone:ENTRY
GO:1137
:1135	// CheckSoundControllerTone:got_tone
RET:1
:1136	// CheckSoundControllerTone:PrepTone
SET:theTone:AU_AiboTone_ID
SET:AU_AiboTone:0
GO:1135
:1137	// CheckSoundControllerTone:Tone?
WAIT:1
IF_1ST:AU_AiboTone:<>:0:1136
GO:1138
:1138	// CheckSoundControllerTone:no_tone
RET:2
EXIT
:1139	// Handle_Tones:ENTRY
GO:1147
:1140	// Handle_Tones:done
RET:1
:1141	// Handle_Tones:Stand
PLAY:ACTION:STAND
WAIT
GO:1140
:1142	// Handle_Tones:Sit
PLAY:ACTION:SIT
WAIT
GO:1140
:1143	// Handle_Tones:Lie
PLAY:ACTION:LIE
WAIT
GO:1140
:1144	// Handle_Tones:Fwd
PLAY:ACTION:WALK:0:10000
SET:isWalking:1
GO:1140
:1145	// Handle_Tones:Rev
PLAY:ACTION:WALK:180:10000
SET:isWalking:1
GO:1140
:1146	// Handle_Tones:Stop
PLAY:ACTION:STOP_WALK
WAIT
SET:isWalking:0
GO:1140
:1147	// Handle_Tones:Sit_Std_Lie?
WAIT:1
IF_1ST:theTone:=:11:1141
IF_1ST:theTone:=:12:1142
IF_1ST:theTone:=:13:1143
GO:1148
:1148	// Handle_Tones:Fwd_Rev_Stop?
WAIT:1
IF_1ST:theTone:=:23:1144
IF_1ST:theTone:=:25:1145
IF_1ST:theTone:=:24:1146
GO:1149
:1149	// Handle_Tones:TurnL_R?
WAIT:1
IF_1ST:theTone:=:28:1150
IF_1ST:theTone:=:29:1151
GO:1140
:1150	// Handle_Tones:TurnL
PLAY:ACTION:MOVE.TURN.NORMAL:10000
SET:isWalking:1
GO:1140
:1151	// Handle_Tones:TurnR
PLAY:ACTION:MOVE.TURN.NORMAL:-10000
SET:isWalking:1
GO:1140
EXIT
:1152	// CheckRhythm:ENTRY
GO:1155
:1153	// CheckRhythm:got_rhythm
RET:1
:1154	// CheckRhythm:ResetRhythm
SET:AP_Tone:0
GO:1153
:1155	// CheckRhythm:Rhythm?
WAIT:1
IF_1ST:AP_Tone:<>:0:1154
GO:1156
:1156	// CheckRhythm:no_rhythm
RET:2
EXIT
:1157	// Handle_Dance:ENTRY
:1158	// Handle_Dance:Pick_Dance
CALL:1017
CASE:1:GO:1159
CASE:2:GO:1161
CASE:3:GO:1162
CASE:4:GO:1163
CASE:5:GO:1164
CASE:6:GO:1165
EXIT
:1159	// Handle_Dance:DANCE1
PLAY:ACTION+:DANCE1
WAIT
:1160	// Handle_Dance:done
RET:1
:1161	// Handle_Dance:DANCE2
PLAY:ACTION+:DANCE2
WAIT
GO:1160
:1162	// Handle_Dance:DANCE3
PLAY:ACTION+:DANCE3
WAIT
GO:1160
:1163	// Handle_Dance:DANCE4
PLAY:ACTION+:DANCE4
WAIT
GO:1160
:1164	// Handle_Dance:DANCE5
PLAY:ACTION+:DANCE5
WAIT
GO:1160
:1165	// Handle_Dance:DANCE6
PLAY:ACTION+:DANCE6
WAIT
GO:1160
EXIT
:1166	// CheckHitHead:START
:1167	// CheckHitHead:Head_Hit?
WAIT:1
IF_1ST:Head_Hit:>:0:1168
GO:1170
:1168	// CheckHitHead:INIT
SET:Head_Hit:0
:1169	// CheckHitHead:Head_Hit
RET:1
:1170	// CheckHitHead:NONE
RET:2
EXIT
:1171	// CheckTouchHead:START
GO:1174
:1172	// CheckTouchHead:Head_ON
RET:1
:1173	// CheckTouchHead:INIT
SET:Head_ON:0
GO:1172
:1174	// CheckTouchHead:Head_ON?
WAIT:1
IF_1ST:Head_ON:>:0:1173
GO:1175
:1175	// CheckTouchHead:NONE
RET:2
EXIT
:1176	// CheckJaw:START
:1177	// CheckJaw:Jaw_ON?
WAIT:1
IF_1ST:Jaw_ON:=:1:1178
GO:1180
:1178	// CheckJaw:INIT
SET:Jaw_ON:0
:1179	// CheckJaw:Jaw_ON
RET:1
:1180	// CheckJaw:NONE
RET:2
EXIT
:1181	// Main_Not_Walking:ENTRY
GO:1184
:1182	// Main_Not_Walking:Back_ON?
WAIT:1
IF_1ST:Back_ON:>:0:1183
GO:1198
:1183	// Main_Not_Walking:BackMode
CALL:1033
CASE:1:GO:1201
EXIT
:1184	// Main_Not_Walking:Voice?
CALL:1068
CASE:1:GO:1185
CASE:2:GO:1188
EXIT
:1185	// Main_Not_Walking:Handle_VoiceCommands
CALL:1073
CASE:1:GO:1201
EXIT
:1186	// Main_Not_Walking:yowl
PLAY:ACTION+:yowl
WAIT
GO:1201
:1187	// Main_Not_Walking:purr
PLAY:ACTION+:purr
WAIT
GO:1201
:1188	// Main_Not_Walking:AiboSound?
CALL:1129
CASE:1:GO:1189
CASE:2:GO:1190
EXIT
:1189	// Main_Not_Walking:growl
PLAY:ACTION+:growl
WAIT
GO:1201
:1190	// Main_Not_Walking:Tone?
CALL:1134
CASE:1:GO:1191
CASE:2:GO:1192
EXIT
:1191	// Main_Not_Walking:Handle_Tones
CALL:1139
CASE:1:GO:1201
EXIT
:1192	// Main_Not_Walking:Rhythm?
CALL:1152
CASE:1:GO:1193
CASE:2:GO:1195
EXIT
:1193	// Main_Not_Walking:Dance
CALL:1157
CASE:1:GO:1201
EXIT
:1194	// Main_Not_Walking:hair_ball
PLAY:ACTION+:hair_ball
WAIT
GO:1201
:1195	// Main_Not_Walking:HitHead?
CALL:1166
CASE:1:GO:1186
CASE:2:GO:1196
EXIT
:1196	// Main_Not_Walking:TouchHead?
CALL:1171
CASE:1:GO:1187
CASE:2:GO:1197
EXIT
:1197	// Main_Not_Walking:Jaw?
CALL:1176
CASE:1:GO:1194
CASE:2:GO:1182
EXIT
:1198	// Main_Not_Walking:(spacer)
GO:1200
:1199	// Main_Not_Walking:whats_up
PLAY:ACTION+:whats_up
WAIT
GO:1201
:1200	// Main_Not_Walking:20_sec_timeout
CALL:1246
CASE:1:GO:1199
CASE:2:GO:1202
EXIT
:1201	// Main_Not_Walking:ResetTimeout
CALL:1252
CASE:1:GO:1203
EXIT
:1202	// Main_Not_Walking:done
RET:1
:1203	// Main_Not_Walking:Clear_Inputs
CLR:SENSORS
GO:1202
EXIT
:1204	// Main_Walking:ENTRY
GO:1206
:1205	// Main_Walking:RETURN
RET:1
:1206	// Main_Walking:Obstacle?
WAIT:1
IF_1ST:Distance:<:200:1207
GO:1214
:1207	// Main_Walking:React_and_stop
PLAY:ACTION+:whats_up
PLAY:ACTION:STOP_WALK
WAIT
SET:isWalking:0
GO:1205
:1208	// Main_Walking:Voice?
CALL:1068
CASE:1:GO:1212
CASE:2:GO:1232
EXIT
:1209	// Main_Walking:Fwd
PLAY:ACTION:WALK:0:10000
SET:isWalking:1
GO:1205
:1210	// Main_Walking:Rev
PLAY:ACTION:WALK:180:10000
SET:isWalking:1
GO:1205
:1211	// Main_Walking:Stop
PLAY:ACTION:STOP_WALK
WAIT
SET:isWalking:0
GO:1205
:1212	// Main_Walking:Fwd_Rev_Stop?
WAIT:1
IF_1ST:theVoiceCmd:=:35:1209
IF_1ST:theVoiceCmd:=:36:1210
IF_1ST:theVoiceCmd:=:38:1211
GO:1213
:1213	// Main_Walking:TurnL_R?
WAIT:1
IF_1ST:theVoiceCmd:=:34:1221
IF_1ST:theVoiceCmd:=:33:1222
GO:1215
:1214	// Main_Walking:TouchHead?
CALL:1171
CASE:1:GO:1207
CASE:2:GO:1208
EXIT
:1215	// Main_Walking:ComeHere?
WAIT:1
IF_1ST:theVoiceCmd:=:54:1216
GO:1231
:1216	// Main_Walking:TurnInDirectionOfVoice
CALL:1118
CASE:1:GO:1217
EXIT
:1217	// Main_Walking:StartWalking
PLAY:ACTION:WALK:0:1000
SET:isWalking:1
GO:1205
:1218	// Main_Walking:(spacer2)
GO:1205
:1219	// Main_Walking:Faster_Slower?
WAIT:1
IF_1ST:theVoiceCmd:=:39:1220
IF_1ST:theVoiceCmd:=:40:1243
GO:1234
:1220	// Main_Walking:Fwd_FAST
PLAY:ACTION+:wink03
PLAY:ACTION:WALK.STYLE3:0:10000
SET:isWalking:1
GO:1205
:1221	// Main_Walking:TurnL
PLAY:ACTION:MOVE.TURN.NORMAL:10000
SET:isWalking:1
GO:1205
:1222	// Main_Walking:TurnR
PLAY:ACTION:MOVE.TURN.NORMAL:-10000
SET:isWalking:1
GO:1205
:1223	// Main_Walking:Fwd(2)
PLAY:ACTION:WALK:0:10000
SET:isWalking:1
GO:1205
:1224	// Main_Walking:Rev(2)
PLAY:ACTION:WALK:180:10000
SET:isWalking:1
GO:1205
:1225	// Main_Walking:Stop(2)
PLAY:ACTION:STOP_WALK
WAIT
SET:isWalking:0
GO:1205
:1226	// Main_Walking:Fwd_Rev_Stop?(2)
WAIT:1
IF_1ST:theTone:=:23:1223
IF_1ST:theTone:=:25:1224
IF_1ST:theTone:=:24:1225
GO:1227
:1227	// Main_Walking:TurnL_R?(2)
WAIT:1
IF_1ST:theTone:=:28:1228
IF_1ST:theTone:=:29:1229
GO:1237
:1228	// Main_Walking:TurnL(2)
PLAY:ACTION:MOVE.TURN.NORMAL:10000
SET:isWalking:1
GO:1205
:1229	// Main_Walking:TurnR(2)
PLAY:ACTION:MOVE.TURN.NORMAL:-10000
SET:isWalking:1
GO:1205
:1230	// Main_Walking:Tone?
CALL:1134
CASE:1:GO:1226
CASE:2:GO:1237
EXIT
:1231	// Main_Walking:Take_Picture?
WAIT:1
IF_1ST:theVoiceCmd:=:55:1233
GO:1219
:1232	// Main_Walking:(spacer1)
GO:1230
:1233	// Main_Walking:TakeUpskirtPicture
CALL:1255
CASE:1:GO:1205
EXIT
:1234	// Main_Walking:Action_1_2_3_4?
WAIT:1
IF_1ST:theVoiceCmd:=:49:1244
IF_1ST:theVoiceCmd:=:50:1235
IF_1ST:theVoiceCmd:=:51:1236
IF_1ST:theVoiceCmd:=:52:1245
GO:1232
:1235	// Main_Walking:Fwd_SmallSteps
PLAY:ACTION:WALK.STYLE36:0:10000
SET:isWalking:1
GO:1205
:1236	// Main_Walking:Fwd_Bandy2
PLAY:ACTION:WALK.STYLE40:0:10000
SET:isWalking:1
GO:1205
:1237	// Main_Walking:Tail31x?
WAIT:1
IF_1ST:Tail_U_ON:>:0:1238
IF_1ST:Tail_D_ON:>:0:1239
IF_1ST:Tail_R_ON:>:0:1241
IF_1ST:Tail_L_ON:>:0:1240
GO:1218
:1238	// Main_Walking:Fwd(3)
PLAY:ACTION:WALK:0:10000
SET:isWalking:1
GO:1242
:1239	// Main_Walking:Rev(3)
PLAY:ACTION:WALK:180:10000
SET:isWalking:1
GO:1242
:1240	// Main_Walking:TurnL(3)
PLAY:ACTION:MOVE.TURN.NORMAL:10000
SET:isWalking:1
GO:1242
:1241	// Main_Walking:TurnR(3)
PLAY:ACTION:MOVE.TURN.NORMAL:-10000
SET:isWalking:1
:1242	// Main_Walking:ClearTail
SET:Tail_U_ON:0
SET:Tail_D_ON:0
SET:Tail_L_ON:0
SET:Tail_R_ON:0
GO:1205
:1243	// Main_Walking:Fwd_SLOW
PLAY:ACTION+:wink48
PLAY:ACTION:WALK.STYLE1:0:10000
SET:isWalking:1
GO:1205
:1244	// Main_Walking:Fwd_Bandy
PLAY:ACTION:WALK.STYLE32:0:10000
SET:isWalking:1
GO:1205
:1245	// Main_Walking:Fwd_Bandy2(3)
PLAY:ACTION:WALK.STYLE44:0:10000
SET:isWalking:1
GO:1205
EXIT
:1246	// CheckIdleTimeout20:ENTRY
GO:1249
:1247	// CheckIdleTimeout20:timed_out
RET:1
:1248	// CheckIdleTimeout20:Wait_50ms_bump
WAIT:50
ADD:idle_count:1
GO:1250
:1249	// CheckIdleTimeout20:Idle_Timeout?
WAIT:1
IF_1ST:idle_count:>:200:1251
GO:1248
:1250	// CheckIdleTimeout20:nope
RET:2
:1251	// CheckIdleTimeout20:ResetTimeout
CALL:1252
CASE:1:GO:1247
EXIT
EXIT
:1252	// ResetTimeout:ENTRY
GO:1254
:1253	// ResetTimeout:RETURN
RET:1
:1254	// ResetTimeout:ResetTimeout
SET:idle_count:0
GO:1253
EXIT
:1255	// TakeAPicture_Upskirt:ENTRY
GO:1260
:1256	// TakeAPicture_Upskirt:RETURN
RET:1
:1257	// TakeAPicture_Upskirt:Snapshot
PLAY:ACTION:PHOTOSNAP
AP_SNAPSHOT
:1258	// TakeAPicture_Upskirt:wait_for_it
WAIT:1
IF_1ST:AP_Snap_Ready:>:0:1263
GO:1258
:1259	// TakeAPicture_Upskirt:Save_it
PLAY:ACTION+:eye_redlong
VLOAD:snapNum
AP_SAVEIMAGE:snapNum
ADD:snapNum:1
VSAVE:snapNum
PLAY:ACTION+:eye_greenshort
WAIT
GO:1256
:1260	// TakeAPicture_Upskirt:Stop
PLAY:ACTION:STOP_WALK
WAIT
SET:isWalking:0
:1261	// TakeAPicture_Upskirt:Sit_Down
PLAY:ACTION:SIT
WAIT
:1262	// TakeAPicture_Upskirt:Look_up_skirt
PLAY:ACTION:MOVE.HEAD.FAST:0:90
WAIT
GO:1257
:1263	// TakeAPicture_Upskirt:Restore_modesty
PLAY:ACTION:MOVE.HEAD.FAST:0:0
WAIT
GO:1259
EXIT
:1264	// INCLUDE_CUSTOM_RCR:Main:START
GO:1266
:1265	// INCLUDE_CUSTOM_RCR:Main:Include_RCR
HALT
#AP_INCLUDE /MS/CUSTOM/RCRLIB.R
GO:1267
:1266	// INCLUDE_CUSTOM_RCR:Main:pretend_test
WAIT:1
IF_1ST:1:=:1:1267
GO:1265
:1267	// INCLUDE_CUSTOM_RCR:Main:done
RET:1
EXIT
