(function(){

    function createImage(src){
      let img = document.createElement('img');
      img.src = src;

      return img;
    }


    let selectors = ['[skype-image]', '[whatsapp-image]', '[viber-image]', '[telegram-image]'];
    let srcs_off = ['image/skype_off.png', 'image/whatsapp_off.png', 'image/viber_off.png', 'image/telegram_off.png'];
    let srcs_on = ['image/skype_on.png', 'image/whatsapp_on.png', 'image/viber_on.png', 'image/telegram_on.png'];

    for(let i = 0; i < 4; i++){
      document.querySelector(selectors[i]).addEventListener('mouseover', function(event){
        let fb = document.querySelector(selectors[i]);
        fb.replaceChild(createImage(srcs_on[i]), fb.querySelector('img'));
      });

      document.querySelector(selectors[i]).addEventListener('mouseout', function(event){
        let fb = document.querySelector(selectors[i]);
        fb.replaceChild(createImage(srcs_off[i]), fb.querySelector('img'));
      });
    }

    document.querySelector('[fb-image]').onmouseout = function(){
      let fb = document.querySelector('[fb-image]');
      fb.replaceChild(createImage("image/fb_off.png"), fb.querySelector('img'));
    }

    document.querySelector('[fb-image]').addEventListener('mouseover', function(event){
      let fb = document.querySelector('[fb-image]');
      fb.replaceChild(createImage("image/fb_on.png"), fb.querySelector('img'));
    });

    document.querySelector('[inst-image]').addEventListener('mouseout', function(event){
      let fb = document.querySelector('[inst-image]');
      fb.replaceChild(createImage("image/inst_off.png"), fb.querySelector('img'));
    });

    document.querySelector('[inst-image]').addEventListener('mouseover', function(event){
      let fb = document.querySelector('[inst-image]');
      fb.replaceChild(createImage("image/inst_on.png"), fb.querySelector('img'));
    });

    let tooltip;

    document.onmouseover = function(event) {

      let anchorElem = event.target.closest('[data-tooltip]');

      if (!anchorElem) return;

      tooltip = showTooltip(anchorElem, anchorElem.dataset.tooltip);
    }

    document.onmouseout = function() {

      if (tooltip) {
        tooltip.remove();
        tooltip = false;
      }

    }


    function showTooltip(anchorElem, html) {
      let tooltipElem = document.createElement('div');
      tooltipElem.className = 'tooltip';
      tooltipElem.innerHTML = html;
      document.body.append(tooltipElem);

      let coords = anchorElem.getBoundingClientRect();

      let left = coords.left + (anchorElem.offsetWidth - tooltipElem.offsetWidth) / 2;
      if (left < 0) left = 0;

      let top = coords.top - tooltipElem.offsetHeight - 5;
      if (top < 0) {
        top = coords.top + anchorElem.offsetHeight + 5;
      }

      
      tooltipElem.style.textAlign = "center";
      tooltipElem.style.marginLeft = 100 + 'px';
      tooltipElem.style.left = left + 'px';
      tooltipElem.style.top = top + 'px';
      tooltipElem.style.color = "white";
      tooltipElem.style.backgroundColor = "#493a3a";
      tooltipElem.style.fontSize = 14 + 'px';
      tooltipElem.style.width = 200 + 'px';

      return tooltipElem;
    }

})();
