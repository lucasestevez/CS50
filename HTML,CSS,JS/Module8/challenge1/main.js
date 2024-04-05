const navbar_button = document.querySelector(".navbar-toggler");

const CLASS_SHOW = 'show';

navbar_button.addEventListener('click', () => {

    const menu_id = navbar_button.getAttribute("data-bs-target");
    const menu = document.querySelector(menu_id);

    let is_showing = false;
    for (let item of menu.classList) {
        
        if (item == CLASS_SHOW) {
            is_showing = true;
            break;
        }
        
    }
    
    if (is_showing) {
        menu.classList.remove(CLASS_SHOW);

    } else {
        menu.classList.add(CLASS_SHOW);
    }
    


});