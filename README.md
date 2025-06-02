# paramount_controller_working
i have made paramount controller for controlling the barrier 



frontened ka exe kaise banate hai. so hum windows ke exe ke liye electron ka use karte hai. lekin agar hum chahte hai ki mera ek exe ho jisse mera frontened windows me open na hokar browser me open ho to mujhe ye chiz apply karni padegi. 

step-1) sabse pahle ek server.js ke name se file banao. jo ki main project ke andar ye file rahegi.

const { exec } = require('child_process');
exec('npx serve -s dist -l 3000');
exec('start http://localhost:3000');

step-2) run the npm run build. 

step-3) pkg server.js --targets node18-win-x64 --output SaralaxeIndia.exe

step-4) agar hume client ka image se exe banani hai to hum wo bhi kar sakte hai
