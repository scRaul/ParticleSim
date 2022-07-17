let frames = 600 ;
let screen = document.getElementById("screen");


function sleep(ms){
  return new Promise(resolve => setTimeout(resolve, ms))
}

var n = 0; 
const delay = 1000 / 60; 
async function update(){
    let start = new Date().getTime(); 
    screen.style.backgroundImage = "url('img/" + n + ".png')";
    n++;
    if(n == frames)
        n = 0; 
    await sleep(start + delay - new Date().getTime())
    update();
}

update();







































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































