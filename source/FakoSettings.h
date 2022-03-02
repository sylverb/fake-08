#pragma once

#include <string>

#ifndef VER_STR
#define VER_STR "v0.0.0.0"
#endif


const char * fake08SettingsP8 = R"#(
pico-8 cartridge // http://www.pico-8.com
version 33
__lua__
function _init()
	
	if not __getsetting then
		printh('not in fake-08 (or unimplemented...), stubbing get and set functions!')
		function __getsetting(sn)
			printh('trying to get setting ' .. sn)
			return 0
		end
		
		function __setsetting(sn,v)
			printh('trying to set setting ' .. sn .. ' to '..v)
		end
		
	end
	
	settinglist = {'kbmode','enableresize','stretch','menustyle'}
	settings = {}
	for i,v in ipairs(settinglist) do
		settings[v] = __getsetting(v) + 1
	end
	
	list = {
		{name='input',ops = {
			{
				name = 'keyboard mode',
				vn = 'kbmode',
				ch ={'emoji','lowercase'}
			}
		}},
		{name='audio',ops = {
			
		}},
		{name='video',ops = {
			{
				name = 'enable resize hotkeys',
				vn = 'enableresize',
				ch ={'no','yes'}
			},
			{
				name = 'stretch mode',
				vn = 'stretch',
				ch ={'pixel perfect','pixel perfect stretch','stretch to fit','overflow stretch','alt screen pixel perfect','alt screen stretch'}
			}
		}},
		{name='menu',ops = {
			{
				name = 'menu style',
				vn = 'menustyle',
				ch ={'classic','carts','splore'}
			}
		}}
	}
	
	path = {}
	
	menuspace = 10
	indent = 10
	basex = 10
	basey = 20
	
	cursorpos = 1
	
	cpath = nil
	sectionname = nil
	numitems = nil
	inoption = false
	cvariable = nil
	cvalue = nil
	
	refreshinfo()
	
end
-->8

function refreshinfo()

	cpath = list
	sectionname = 'main'
	for i,v in ipairs(path) do
		cpath = cpath[v]
		sectionname = cpath.name
		cvariable = cpath.vn
		cvalue = settings[cvariable]
		if cpath.ops then
			cpath = cpath.ops
			inoption = false
		end
		if cpath.ch then
			cpath = cpath.ch
			inoption = true
		end
	end

	numitems = #cpath + 1
end

function updatecursor()
	cursorpos -= 1
	if btnp( ⬆️ ) then
		cursorpos -= 1
	end
	if btnp( ⬇️ ) then
		cursorpos += 1
	end
	cursorpos = (cursorpos % numitems) + 1
	
	if btnp( ❎ ) or btnp ( 🅾️ ) then
		printh('cursorpos - 1: ' .. cursorpos-1)
		if cursorpos == numitems then -- back
			cursorpos = deli(path)
			if not cursorpos then
				--exit to bios
				__loadbioscart()
			end
		else
			if inoption then
				settings[cvariable] = cursorpos
				__setsetting(cvariable,cursorpos-1)
			else
				add(path,cursorpos)
			end
		end
		refreshinfo()
	end
end

function _update60()
	
	updatecursor()
	
end
-->8

function drawitem(n,y,x)
	local yoffset = (menuspace*y)
	color(7)
	print(n,x,20+yoffset)
	color(6)
	line(4,22+yoffset,x-2,22+yoffset)
	line(4,22+yoffset,4,22)
	if cvalue == y then
		line(x,18+yoffset,x + (4 * #n) - 2,18+yoffset)
		line(x,26+yoffset,x + (4 * #n) - 2,26+yoffset)
	end
end

function drawcursor()
	if cursorpos then --unknown why this matters?
		spr(5,13,18+(menuspace*cursorpos),1,2)
	end
end

function _draw()
	cls(1)
	spr(0,1,1,5,1)
	

	color(7)
	drawitem(sectionname,0,10)
	
	local lasti = 0
	if inoption then
		for i,v in ipairs(cpath) do
			drawitem(v,i,20)
			lasti = i
		end
	else
		for i,v in ipairs(cpath) do
			drawitem(v.name,i,20)
			lasti = i
		end
	end
	lasti += 1
	drawitem('back',lasti,20)
	drawcursor()
end
__gfx__
77777077777077007077777000000077770077771110000000000000000000000000000000000000000000000000000000000000000000000000000000000000
77000077077077077077000000000770770770771771000000000000000000000000000000000000000000000000000000000000000000000000000000000000
77777077777077770077770077770770770777770117100000000000000000000000000000000000000000000000000000000000000000000000000000000000
77000077077077077077000000000770770770770001710000000000000000000000000000000000000000000000000000000000000000000000000000000000
77000077077077007077777000000777700777700000071000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000001710000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000117100000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000001771000000000000000000000000000000000000000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000001110000000000000000000000000000000000000000000000000000000000000000000000000000000000000

)#";