# paramount_controller_working
i have made paramount controller for controlling the barrier 



frontened ka exe kaise banate hai. so hum windows ke exe ke liye electron ka use karte hai. lekin agar hum chahte hai ki mera ek exe ho jisse mera frontened windows me open na hokar browser me open ho to mujhe ye chiz apply karni padegi. 

step-0) npm install -g pkg
step-1) npm install serve-handler
step-2) sabse pahle ek server.js ke name se file banao. jo ki main project ke andar ye file rahegi.

const { exec } = require('child_process');
exec('npx serve -s dist -l 3000');
exec('start http://localhost:3000');

step-3) run the npm run build. 

step-4) pkg server.js --targets node18-win-x64 --output SaralaxeIndia.exe

step-5) agar hume client ka image se exe banani hai to hum wo bhi kar sakte hai

step-6) isko run krne ke liye dist folder chahiye aur dist folder ke bahar ye meri exe hono chahiye tbhi ye exe jo hai dist folder me jo files hai unko serve karti hai browser me means ki meri website ko, aur mera package.json file bhi hona chahiye dependency ke liye. so agar mujhe kisi client ke pc me ye chiz dalni hai to mere pass dist folder, exe aur package.json file hona chahiye
