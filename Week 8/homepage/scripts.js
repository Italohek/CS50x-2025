// Wait for the page to fully load
document.addEventListener('DOMContentLoaded', function() {
    // Select the contact form
    const contactForm = document.getElementById('contact-form');

    // Check if the form exists on the current page
    if (contactForm) {
        // Add an event listener for when the form is submitted
        contactForm.addEventListener('submit', function(event) {
            // Prevent the default form submission (which reloads the page)
            event.preventDefault();

            // Get the values from the form fields
            const email = document.getElementById('email').value;

            // Show a confirmation alert
            alert(`Thank you for your message, ${email}! I will get back to you soon.`);

            // Clear the form fields after submission
            contactForm.reset();
        });
    }
});
