const API_URL = 'http://localhost:8080';

function showResult(content, type = 'info') {
    const resultDiv = document.getElementById('result');
    resultDiv.innerHTML = content;
    resultDiv.className = `result show ${type}`;
    
    setTimeout(() => {
        resultDiv.scrollIntoView({ behavior: 'smooth', block: 'nearest' });
    }, 100);
}

async function addUser() {
    const user = document.getElementById('newUser').value.trim();
    
    if (!user) {
        showResult('<h3>Error</h3><p>Please enter a username</p>', 'error');
        return;
    }
    
    try {
        const response = await fetch(`${API_URL}/add-user`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ user })
        });
        
        const data = await response.json();
        
        if (data.success) {
            showResult(`<h3>Success</h3><p>User "${user}" added successfully!</p>`, 'success');
            document.getElementById('newUser').value = '';
        } else {
            showResult(`<h3>Error</h3><p>${data.message}</p>`, 'error');
        }
    } catch (error) {
        showResult('<h3>Error</h3><p>Failed to connect to server. Make sure the backend is running.</p>', 'error');
    }
}

async function addFriendship() {
    const user1 = document.getElementById('user1').value.trim();
    const user2 = document.getElementById('user2').value.trim();
    
    if (!user1 || !user2) {
        showResult('<h3>Error</h3><p>Please enter both usernames</p>', 'error');
        return;
    }
    
    try {
        const response = await fetch(`${API_URL}/add-friend`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ user1, user2 })
        });
        
        const data = await response.json();
        
        if (data.success) {
            showResult(`<h3>Success</h3><p>Friendship between "${user1}" and "${user2}" added!</p>`, 'success');
            document.getElementById('user1').value = '';
            document.getElementById('user2').value = '';
        } else {
            showResult(`<h3>Error</h3><p>${data.message}</p>`, 'error');
        }
    } catch (error) {
        showResult('<h3>Error</h3><p>Failed to connect to server. Make sure the backend is running.</p>', 'error');
    }
}

async function getFriends() {
    const user = document.getElementById('userForFriends').value.trim();
    
    if (!user) {
        showResult('<h3>Error</h3><p>Please enter a username</p>', 'error');
        return;
    }
    
    try {
        const response = await fetch(`${API_URL}/friends?user=${encodeURIComponent(user)}`);
        const data = await response.json();
        
        if (data.success) {
            if (data.friends.length === 0) {
                showResult(`<h3>Friends of "${user}"</h3><p>No friends yet.</p>`, 'info');
            } else {
                const friendsList = data.friends.map(f => `<li>${f}</li>`).join('');
                showResult(`<h3>Friends of "${user}"</h3><ul>${friendsList}</ul>`, 'info');
            }
        } else {
            showResult(`<h3>Error</h3><p>${data.message}</p>`, 'error');
        }
    } catch (error) {
        showResult('<h3>Error</h3><p>Failed to connect to server. Make sure the backend is running.</p>', 'error');
    }
}

async function getMutualFriends() {
    const user1 = document.getElementById('mutualUser1').value.trim();
    const user2 = document.getElementById('mutualUser2').value.trim();
    
    if (!user1 || !user2) {
        showResult('<h3>Error</h3><p>Please enter both usernames</p>', 'error');
        return;
    }
    
    try {
        const response = await fetch(`${API_URL}/mutual?user1=${encodeURIComponent(user1)}&user2=${encodeURIComponent(user2)}`);
        const data = await response.json();
        
        if (data.success) {
            if (data.mutualFriends.length === 0) {
                showResult(`<h3>Mutual Friends</h3><p>"${user1}" and "${user2}" have no mutual friends.</p>`, 'info');
            } else {
                const mutualList = data.mutualFriends.map(f => `<li>${f}</li>`).join('');
                showResult(`<h3>Mutual Friends of "${user1}" and "${user2}"</h3><ul>${mutualList}</ul>`, 'info');
            }
        } else {
            showResult(`<h3>Error</h3><p>${data.message}</p>`, 'error');
        }
    } catch (error) {
        showResult('<h3>Error</h3><p>Failed to connect to server. Make sure the backend is running.</p>', 'error');
    }
}

async function getShortestPath() {
    const user1 = document.getElementById('pathUser1').value.trim();
    const user2 = document.getElementById('pathUser2').value.trim();
    
    if (!user1 || !user2) {
        showResult('<h3>Error</h3><p>Please enter both usernames</p>', 'error');
        return;
    }
    
    try {
        const response = await fetch(`${API_URL}/shortest-path?user1=${encodeURIComponent(user1)}&user2=${encodeURIComponent(user2)}`);
        const data = await response.json();
        
        if (data.success) {
            if (data.path.length === 0) {
                showResult(`<h3>Shortest Path (BFS)</h3><p>No path exists between "${user1}" and "${user2}".</p>`, 'error');
            } else {
                const pathDisplay = data.path.map((user, index) => {
                    if (index === data.path.length - 1) {
                        return `<span class="path-item">${user}</span>`;
                    }
                    return `<span class="path-item">${user}</span><span class="arrow">→</span>`;
                }).join('');
                
                const distance = data.path.length - 1;
                showResult(`<h3>Shortest Path (BFS)</h3><p>${pathDisplay}</p><p><strong>Distance: ${distance} ${distance === 1 ? 'hop' : 'hops'}</strong></p>`, 'success');
            }
        } else {
            showResult(`<h3>Error</h3><p>${data.message}</p>`, 'error');
        }
    } catch (error) {
        showResult('<h3>Error</h3><p>Failed to connect to server. Make sure the backend is running.</p>', 'error');
    }
}

document.addEventListener('keypress', function(event) {
    if (event.key === 'Enter') {
        const activeElement = document.activeElement;
        
        if (activeElement.id === 'newUser') {
            addUser();
        } else if (activeElement.id === 'user1' || activeElement.id === 'user2') {
            addFriendship();
        } else if (activeElement.id === 'userForFriends') {
            getFriends();
        } else if (activeElement.id === 'mutualUser1' || activeElement.id === 'mutualUser2') {
            getMutualFriends();
        } else if (activeElement.id === 'pathUser1' || activeElement.id === 'pathUser2') {
            getShortestPath();
        }
    }
});
