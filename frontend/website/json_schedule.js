// const data = { schedule: "1" };
fetch('JSON/example_schedule.json', {
    method: "GET", // or 'PUT'
    headers: {
        "Accept": "application/json",
    },
    // body: JSON.stringify(data),
})
.then(response => response.json())
.then(json => console.log(json));
    // .then((data) => {
    //     console.log("Success:", data);
    // })
    // .catch((error) => {
    //     console.error("Error:", error);
    // });