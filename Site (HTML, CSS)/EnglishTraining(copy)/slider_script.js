(function(){
    onload = function ()
    {
    let grounds = ["image/aleksandr.png",
                   "image/slavica.png",
                   "image/maria.png",
                   "image/anna.png",
                   "image/nicolas.png"];
    let t = 5;
    
    document.getElementById("div_slider").style.backgroundImage = 'url(' + grounds[4] + ')';
    setInterval (function ()
       {
       let p = grounds.shift ();
       document.getElementById("div_slider").style.backgroundImage = 'url(' + p + ')';
       grounds.push (p);
       }, t * 1000);
}
})();
