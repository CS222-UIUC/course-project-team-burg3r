function menuToggle() {
    document.getElementById("dropdown").classList.toggle("show");
}

function addCourse() {
    var course = {
        subject: document.getElementById("subject").value,
        number: document.getElementById("number").value
    };
            
    // currently just displays the value added (to change)
    alert(JSON.stringify(course));
}

function submitCourses() {
    var courses = document.getElementsByClassName("course")

    // currently just displays all courses added (to change)
    alert(JSON.stringify(courses));
}

window.onclick = function(event) {
    if (!event.target.matches('.dropbtn')) {
        var dropdowns = document.getElementsByClassName("dropdown-content");
        var i;
        for (i = 0; i < dropdowns.length; i++) {
        var openDropdown = dropdowns[i];
        if (openDropdown.classList.contains('show')) {
            openDropdown.classList.remove('show');
        }
        }
    }
}