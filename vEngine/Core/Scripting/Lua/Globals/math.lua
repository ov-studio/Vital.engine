----------------------------------------------------------------
--[[ Resource: vEngine: Lua Module
     Script: generic.lua
     Author: vStudio
     Developer(s): Aviril, Mario, Tron
     DOC: 02/01/2022
     Desc: Math Module ]]--
----------------------------------------------------------------


----------------
--[[ Module ]]--
----------------

vEngine.math = math
math = nil

--TODO: ..
function len(T)
  local count = 0
  for _ in pairs(T) do 
	count = count + 1 end
  return count
end

-- linear interpolation
function vEngine.math.lerp(a,b,t)
	return (a + (b-a)*t);
end

-- clamp number between min,max
function vEngine.math.clamp(x,min,max)
	if(x < min) then
		return min
	elseif(x > max) then
		return max
	else
		return x
	end
end

-- clamp number between 0,1
function vEngine.math.saturate(x)
	return vEngine.math.clamp(x,0,1)
end

-- round number to nearest integer
function vEngine.math.round(x)
	return x + 0.5 - ( x + 0.5 ) % 1;
end