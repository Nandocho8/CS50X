$("select").change(function () {
    if ($(this)).val() == 0 {
        $(".shares").attr("disabled", "disabled");
    } else {
        $(".shares").removeAttr("disabled");
    }
}).trigger("change");