-- scripts/play_scene.lua
local circles = {}
print ("Bolas CARGADAS")
function update()
	if rl.mouse_pressed(1) then
		local sx = rl.mouse_x()
		local sy = rl.mouse_y()
		print("Mouse clicked")
		
		table.insert(circles,{x = sx, y = sy,r = 10.0})
	end
end

function draw()
	for _,c in ipairs(circles) do
		rl.draw_circle(c.x,c.y,c.r)
	end
end