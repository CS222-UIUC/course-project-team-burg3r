function menuToggle() {
    document.getElementById("dropdown").classList.toggle("show");
}

function addCourse() {
    var course = {
        subject: document.getElementById("subject").value,
        number: document.getElementById("number").value
    };
    
    alert(JSON.stringify(course));

    if (0){ // check course list if invalid course (to change)
      alert("error: invalid class")
    }
    else {
      // alert(JSON.stringify(course));
      var course_list = document.getElementById("course_list");
      var course_bubble = document.createElement("&#10006; {subject},{number}");
      course_list.appendChild(course_bubble);
      // <button type="button" id="course_bubble" onclick="deleteCourse();">&#10006; subject,number</button>
    }
}

function deleteCourse() {
  var elem = document.getElementById("course_bubble");
  elem.parentNode.removeChild(elem);
}

function submitCourses() {
    var courses = document.getElementsByClassName("course");

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

