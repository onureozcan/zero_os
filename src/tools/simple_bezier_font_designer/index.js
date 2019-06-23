var currentChar = 'l';

var ctx = c.getContext('2d');

const CANVAS_BEZIER_CURVE_SAMPLING = 100;
const CANVAS_MAX_ALLOWED_BEZIER_CONTROL_POINTS = 10;
const PADDING_TOP = 30;
const ZOOM = 1.5;
const SCALE_Y = 1;
const SCALE_X = 1;

var activeInput;

window.onkeypress = function (evt) {
    console.log(evt);
    if (evt.key === 'a') {
        if (activeInput) {
            setActiveInput(
                document.querySelector('*[data-i="' + (activeInput.getAttribute("data-i") * 1 + 1) + '"]'));
            evt.preventDefault();
        }
    }
    if (evt.key === 'q') {
        if (activeInput) {
            setActiveInput(
                document.querySelector('*[data-i="' + (activeInput.getAttribute("data-i") * 1 - 1) + '"]'));
            evt.preventDefault();
        }
    }
}

c.onclick = function (evt) {
    if (activeInput) {
        activeInput.value = `${parseInt(evt.offsetX / ZOOM)},${parseInt(evt.offsetY / ZOOM) - PADDING_TOP}`
    }
    drawFont();
};

(function () {
    drawUI();
    drawFont();
})();

function canvas_draw_line(x, y, x2, y2) {
    ctx.beginPath();
    ctx.strokeStyle = "#FFFFFF";
    ctx.moveTo(x, y + PADDING_TOP);
    ctx.lineTo(x2, y2 + PADDING_TOP);
    ctx.stroke();
}

function canvas_get_interpolated_point(p1, p2, percent) {
    var p = {};
    p.x = (p1.x + percent / CANVAS_BEZIER_CURVE_SAMPLING * (p2.x - p1.x));
    p.y = (p1.y + percent / CANVAS_BEZIER_CURVE_SAMPLING * (p2.y - p1.y));
    return p;
}

function round(d) {
    return Math.round(d);
}

function canvas_draw_bezier_curve_scaled(x, y, points, size_of_points, scale_x, scale_y) {
    var prev_point;
    for (var p = 0; p < CANVAS_BEZIER_CURVE_SAMPLING; p++) {
        var point = canvas_draw_bezier_curve_internal(x, y, points, size_of_points, p);
        if (p != 0)
            canvas_draw_line(round(point.x * scale_x + x), round(point.y * scale_y + y),
                round(prev_point.x * scale_x + x), round(prev_point.y * scale_y + y));
        prev_point = point;
    }
}

function canvas_draw_bezier_curve_internal(x, y, points, size_of_points, percent) {
    if (size_of_points == 0) return;
    if (size_of_points == 2) {
        return canvas_get_interpolated_point(points[0], points[1], percent);
    }
    var new_points = [CANVAS_MAX_ALLOWED_BEZIER_CONTROL_POINTS];

    var new_size = 0;
    for (var i = 0; i < size_of_points - 1; i++) {
        var current = points[i];
        var next = points[i + 1];
        var new_point = canvas_get_interpolated_point(current, next, percent);
        new_points[new_size++] = new_point;
    }
    return canvas_draw_bezier_curve_internal(x, y, new_points, new_size, percent);
}

function setActiveInput(obj) {
    if (activeInput) {
        activeInput.style.borderColor = null;
    }
    activeInput = obj;
    activeInput.style.borderColor = "red";
}

function drawUI() {
    var _tbody = layers_container.querySelector("tbody");
    var count = 0;
    ;
    for (var i = 0; i < CANVAS_MAX_ALLOWED_BEZIER_CONTROL_POINTS; i++) {
        var _tr = document.createElement("tr");
        _tr.innerHTML = `<td>${i}</td><td>`;
        for (var j = 0; j < CANVAS_MAX_ALLOWED_BEZIER_CONTROL_POINTS; j++) {
            count++;
            _tr.innerHTML += `<p>${j})<input data-i="${count}" class="layer_data" onfocus="setActiveInput(this)" placeholder="x,y"/></p>`
        }
        _tbody.appendChild(_tr);
    }
    for (var i = 0; i < 256; i++) {
        document.querySelector("#char_list").innerHTML += `<button onclick="drawCharOverlay(${i})">${String.fromCharCode(i)}</button><br/>`
    }
}

function drawCharOverlay(i) {

    currentChar = String.fromCharCode(i);
    drawFont();

}

function getData() {
    var data = {
        layers: []
    };
    var layerData = document.querySelectorAll(".layer_data");
    for (var i = 0; i < 10; i++) {
        var layer = {
            data: []
        };
        for (var j = 0; j < 10; j++) {
            var val = layerData[i * 10 + j].value;
            if (val)
                layer.data[j] = [val.split(",").map(x => parseInt(x))]
                    .map(v => {
                        return {
                            x: v[0],
                            y: v[1]
                        }
                    })[0];
            else
                break;
        }
        if (layer.data.length)
            data.layers[i] = layer;
        else
            break;
    }
    return data;
}

function clearFont() {
    Array.prototype.slice.call(document.querySelectorAll('input'))
        .forEach(x => x.value = null);
    drawFont();
}

function drawFont() {
    ctx.clearRect(0, 0, c.width, c.height);
    ctx.fillStyle = "#222";
    ctx.font = "normal 130px verdana";
    ctx.textAlign = 'center';
    ctx.textBaseline = 'bottom';
    ctx.fillText(currentChar, 50, 130 + PADDING_TOP);
    var data = getData();
    console.log(data);
    for (var i = 0; i < data.layers.length; i++) {
        var layerData = data.layers[i].data;
        if (layerData.length > 1)
            canvas_draw_bezier_curve_scaled(0, 0,
                layerData, layerData.length, SCALE_X, SCALE_Y);
        for (var j = 0; j < layerData.length; j++) {
            var x = layerData[j].x;
            var y = layerData[j].y;
            ctx.fillStyle = "#a20";
            ctx.font = "15px verdana";
            ctx.fillText(`${j})${x},${y}`, x, y, 40);
        }
    }
}

function getCCode() {
    var data = getData();
    var ret = `void set_bezier_data_${currentChar.charCodeAt(0)}(){\n
        simple_bezier_font_table['${currentChar}'].size = ${data.layers.length};\n`;
    for (var i = 0; i < data.layers.length; i++) {
        var layerData = data.layers[i].data;
        ret +=
            `simple_bezier_font_table['${currentChar}'].layers[${i}] = (simple_bezier_font_layer_t) {
            .size = ${layerData.length},
            .data = {
                ${layerData.map(d => `\t{${parseInt(d.x)},${parseInt(d.y)}}\n`).join(",")}
            }
        };
        `;
    }
    ret += "\n}";
    c_code.innerText = ret;
}
