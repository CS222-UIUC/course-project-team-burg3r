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
        document.getElementById("Results").innerHTML += "Schedule Results";
        document.getElementsByClassName("prev").innerHTML += "&#10094";
        document.getElementsByClassName("next").innerHTML += "&#10095;";
        for (var i=0; i<data.length; i++) {
            sched = data[i];
            var slide = document.createElement("div");
            slide.className = "slide";
            for (var j=0; j<sched.schedule.length; j++) {
                slide.innerHTML += sched.schedule[j].course + "</br>";
            }
            document.getElementsByClassName("results-slideshow").appendChild(slide);
            var dot = document.createElement("span");
            dot.className = "dot";
            dot.onclick = currentSlide(i);
            document.getElementsByClassName("dot").appendChild(dot);
        }
        // document.getElementById("ALL").innerHTML += "last";
        // window.open("results.html");
        
        })
        .catch(function(err) {
            console.log(err)
    })
    
}

var slideIndex = 1;
showSlides(slideIndex);

function plusSlides(n) {
  showSlides(slideIndex += n);
}

function currentSlide(n) {
  showSlides(slideIndex = n);
}

function showSlides(n) {
  var i;
  var slides = document.getElementsByClassName("slide");
  var dots = document.getElementsByClassName("dot");
  if (n > slides.length) {slideIndex = 1}
    if (n < 1) {slideIndex = slides.length}
    for (i = 0; i < slides.length; i++) {
      slides[i].style.display = "none";
    }
    for (i = 0; i < dots.length; i++) {
      dots[i].className = dots[i].className.replace(" active", "");
    }
  slides[slideIndex-1].style.display = "block";
  dots[slideIndex-1].className += " active";
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

let weather = {
    "apiKey": "463a026d4300064311c0be34302d7697",
    fetchWeather: function (city) {
      fetch(
        "https://api.openweathermap.org/data/2.5/weather?q="
        + city
        + "&units=imperial&appid=463a026d4300064311c0be34302d7697"
      )
      .then((response) => response.json())
      .then((data) => this.displayWeather(data));
    },
    fetchWeather2: function () {
      fetch(
        "https://api.openweathermap.org/data/2.5/weather?q="
        + "Champaign"
        + "&units=imperial&appid=463a026d4300064311c0be34302d7697"
      )
      .then((response) => response.json())
      .then((data) => this.displayWeather(data));
    },
    displayWeather : function(data) {
      const { name } = data;
      const { icon, description } = data.weather[0];
      const { temp, humidity } = data.main;
      const { speed } = data.wind;
      console.log(name, icon, description, temp, humidity, speed)
      // document.querySelector(".city").innerText = "Weather in " + name;
      document.querySelector(".description").innerText = description;
      document.querySelector(".temp").innerText = temp + "°F";
      document.querySelector(".humidity").innerText = "Humidity: " + humidity + "%";
      document.querySelector(".wind").innerText = "Wind speed: " + speed + " mph";
  }
};

