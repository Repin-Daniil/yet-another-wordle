# Start the tests via `make test-debug` or `make test-release`

async def test_start(service_client):
    response = await service_client.post(
        '/v1/start',
    )
    assert response.status == 200
    assert len(response.text) == 14


async def test_first_time_users(service_client):
    token = await service_client.post('v1/start').text

    response = await service_client.post(
        '/v1/check',
        params={'token': token, 'word': 'horse'},
    )
    assert response.status == 200
