function menuToggle() {
    document.getElementById("dropdown").classList.toggle("show");
}

// const course_list = document.getElementById("course_list");
// const courses = document.createElement("p");

function addCourse() {
    var course = {
        subject: document.getElementById("subject").value,
        number: document.getElementById("number").value
    };
    
    // alert(JSON.stringify(course));


    if (0){ // check course list if invalid course (to change)
      alert("Invalid class");
    }
    else {
      const new_course = document.createElement("p");
      const new_course_name = document.createTextNode("[" + course.subject + " " + course.number + "]   ");
      new_course.append(new_course_name)
      const course_list = document.getElementById("course_list");
      if (course_list.contains(new_course)) {
        // this doesnt properly prevent duplicate classes -- FIX
        alert("Class has already been added");
      }
      else {
          course_list.append(new_course);
      }
    }
}

function deleteCourse() {
  var elem = document.getElementById("course_bubble");
  elem.parentNode.removeChild(elem);
}

function submitCourses() {
    // dummy window
    var a = window.open('', '', 'height=500, width=500');
    a.document.write('<html>');
    a.document.write('<body > <h1>Course list:<br>');
    for (let i = 0; i < course_list.childNodes.length; i++) {
      a.document.write(course_list.childNodes[i].innerText, '<br>');
    }
    a.document.write('</body></html>');
    // a.document.close();

    // alert(location.pathname);
    fetch('./example.json') // problem reading file
      .then((response) => response.json())
      .then((json) => a.document.write(JSON.stringify(json)));
    a.document.close();
    // alert("DONE?");
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

