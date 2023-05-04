// const dataJson = require('../example.json'); // assert { type: 'JSON' };
// console.log(dataJson);

function menuToggle() {
    document.getElementById("dropdown").classList.toggle("show");
}

// const course_list = document.getElementById("course_list");
// const courses = document.createElement("p");

function addCourse() {
    var course = {
        subject: document.getElementById("subject").value.toUpperCase(),
        number: document.getElementById("number").value
    };
    if (course.subject == "") {
      return;
    }
    if (course.number == "") {
      return;
    }
    
    // alert(JSON.stringify(course));


    if (0){ // check course list if invalid course (to change)
      alert("Invalid class");
    }
    else {
      const course_list = document.getElementById("course_list");
      if (course_list.childElementCount > 0) {
        for (i=0; i<course_list.childElementCount; i++) {
          if (JSON.stringify(course_list.childNodes[i].data) == JSON.stringify(course)) {
            alert("Class has already been added");
            return;
          }
        }
      }
      const new_course = document.createElement("button");
      new_course.textContent = course.subject + " " + course.number;
      new_course.data = course;
      new_course.onclick = function deleteCourse() {
        new_course.parentNode.removeChild(new_course);
      }
      course_list.append(new_course);
    }
}

function submitCourses() {
    // // dummy window
    // var a = window.open('', '', 'height=500, width=500');
    // a.document.write('<html>');
    // a.document.write('<body > <h1>Course list:<br>');
    // for (let i = 0; i < course_list.childNodes.length; i++) {
    //   a.document.write(course_list.childNodes[i].innerText, '<br>');
    // }
    // a.document.write('</body></html>');
    // a.document.close();

    // replace with function to get output from backend
    fetch("JSON/example.json")

    .then(function(response) {
        return response.json();
    })
    .then(function(data) {
        var display = document.createElement("iframe");
        display.setAttribute("src", "schedule_display_example.html");
        display.style.width = "960px";
        display.style.height = "480px";
        display.setAttribute("src", "schedule_display_example.html");
        document.getElementById("result").appendChild(display);
        return;
        document.getElementById("Results").innerHTML = "Schedule Results </br>";
        if (document.getElementById("arrows").childElementCount == 0) {
          const left_button = document.createElement("button");
          left_button.innerHTML = '&#9664';
          const right_button = document.createElement("button");
          right_button.innerHTML = '&#9654';
          left_button.addEventListener('click', () => {
            moveLeft();
            // document.getElementById("Results").innerHTML += "left";
          })
          right_button.addEventListener('click', () => {
            moveRight();
            // document.getElementById("Results").innerHTML += "right";
          })
          document.getElementById("current_slide").value = 0;
          var slide_number = document.createElement("slide_number");
          slide_number.innerHTML = " " + (document.getElementById("current_slide").value+1) + " ";
          document.getElementById("arrows").appendChild(left_button);
          document.getElementById("arrows").appendChild(slide_number);
          document.getElementById("arrows").appendChild(right_button);
        }

        
        

        // document.getElementById("Results").innerHTML += document.getElementById("current_slide").value;

        // document.getElementsByClassName("prev").innerHTML += "&#10094";
        // document.getElementsByClassName("next").innerHTML += "&#10095;";
        for (var i=0; i<data.length; i++) {
            sched = data[i];
            var slide = document.createElement("slide");
            // slide.className = "slide";
            for (var j=0; j<sched.schedule.length; j++) {
                // slide.innerHTML += sched.schedule[j].course + "</br>";
                var course = document.createElement("course");
                course.json = sched.schedule[j];
                slide.appendChild(course);
            }
            document.getElementById("slides").appendChild(slide);
            // var dot = document.createElement("span");
            // dot.className = "dot";
            // dot.onclick = currentSlide(i);
            // document.getElementsByClassName("dot").appendChild(dot);
        }
        displaySlide(0);
        // for (var i=0; i<document.getElementById("slides").childElementCount; i++) {
        //   document.getElementById("Results").innerHTML += i;
        // }

      //   const new_course = document.createElement("button");
      // new_course.textContent = course.subject + " " + course.number;
      // new_course.data = course;
      // new_course.onclick = function deleteCourse() {
      //   new_course.parentNode.removeChild(new_course);
      // }
      // course_list.append(new_course);

        // document.getElementById("ALL").innerHTML += "last";
        // window.open("results.html");
        
        })
        .catch(function(err) {
            console.log(err)
    })
    
}

// var slideIndex = 1;
// showSlides(slideIndex);

// function plusSlides(n) {
//   showSlides(slideIndex += n);
// }

// function currentSlide(n) {
//   showSlides(slideIndex = n);
// }

// function showSlides(n) {
//   var i;
//   var slides = document.getElementsByClassName("slide");
//   var dots = document.getElementsByClassName("dot");
//   if (n > slides.length) {slideIndex = 1}
//     if (n < 1) {slideIndex = slides.length}
//     for (i = 0; i < slides.length; i++) {
//       slides[i].style.display = "none";
//     }
//     for (i = 0; i < dots.length; i++) {
//       dots[i].className = dots[i].className.replace(" active", "");
//     }
//   slides[slideIndex-1].style.display = "block";
//   dots[slideIndex-1].className += " active";
// } 

function moveLeft(){
  if (document.getElementById("slides").childElementCount == 0) {
    return;
  }
  if (document.getElementById("current_slide").value == 0) {
    return;
  }
  document.getElementById("current_slide").value--;
  document.getElementById("arrows").children[1].innerHTML = " " + (document.getElementById("current_slide").value+1) + " ";
  displaySlide(document.getElementById("current_slide").value);
}

function moveRight(){
  if (document.getElementById("slides").childElementCount == 0) {
    return;
  }
  if (document.getElementById("current_slide").value == document.getElementById("slides").childElementCount-1) {
    return;
  }
  document.getElementById("current_slide").value++;
  document.getElementById("arrows").children[1].innerHTML = " " + (document.getElementById("current_slide").value+1) + " ";
  displaySlide(document.getElementById("current_slide").value);
}

function displaySlide(idx){
  // document.getElementById("Results").innerHTML += document.getElementById("current_slide").value;
  document.getElementById("current_slide").innerHTML = "";

  var slide = document.getElementById("slides").children[idx];

  for (var i=0; i<slide.childElementCount; i++) {
    document.getElementById("current_slide").innerHTML += slide.children[i].json.course + "</br>";
  }

  
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



